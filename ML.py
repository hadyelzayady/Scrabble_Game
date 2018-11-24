### Libraries Used
import tensorflow as tf
import numpy as np
import random
import time
import matplotlib.pyplot as plt
from collections import deque# Ordered collection with ends
import warnings # This ignore all the warning messages that are normally printed during the training because of skiimage
warnings.filterwarnings('ignore')
################################################################
#TODO:
#1- Preprocessing for states + actions +score(rewards) + done (optional)
#2- Ask about simple neural networks/ CNN
#3- Ask about state size and action size
#4- Line 127 QS Value is what? when explore probability > exp_exp_tradeoff
######################################################################################
### MODEL HYPERPARAMETERS
# Size of State ( Include Board 15x15x52  plus Rack 7x52)
# state_size = [232,52]
# action_size= [225,52]
state_size = 12064
action_size= 11700
# Array of states and actions
state=[0]
action=[0]
# Learning Rate ( To be Determined)
learning_rate =  0.0002

### TRAINING HYPERPARAMETERS
# TO BE DETERMINED
total_episodes = 500        # Total episodes for training
max_steps = 100              # Max possible steps in an episode
batch_size = 64

# Exploration parameters for epsilon greedy strategy
explore_start = 1.0            # exploration probability at start
explore_stop = 0.01            # minimum exploration probability
decay_rate = 0.0001            # exponential decay rate for exploration prob

# Q learning hyperparameters
gamma = 0.95               # Discounting rate

### MEMORY HYPERPARAMETERS
pretrain_length = batch_size   # Number of experiences stored in the Memory when initialized for the first time
memory_size = 1000          # Number of experiences the Memory can keep

done = False
################################################################################################################

def PreProcessing():
    pass

class DQNetwork:
    def __init__(self, state_size, action_size, learning_rate, name='DQNetwork'):
        self.state_size = state_size
        self.action_size = action_size
        self.learning_rate = learning_rate

        with tf.variable_scope(name):
            # We create the placeholders
            # *state_size means that we take each elements of state_size in tuple hence is like if we wrote
            self.inputs_ = tf.placeholder(tf.float32, [None, state_size], name="inputs")
            self.actions_ = tf.placeholder(tf.float32, [None, action_size], name="actions_")
            # Remember that target_Q is the R(s,a) + ymax Qhat(s', a')
            self.target_Q = tf.placeholder(tf.float32, [None], name="target")


            # now declare the weights connecting the input to the hidden layer
            self.W1 = tf.Variable(tf.random_normal([state_size, 100], stddev=0.03), name='W1')
            self.b1 = tf.Variable(tf.random_normal([100]), name='b1')
            # and the weights connecting the hidden layer to the output layer
            self.W2 = tf.Variable(tf.random_normal([100, 1], stddev=0.03), name='W2')
            self.b2 = tf.Variable(tf.random_normal([1]), name='b2')

            self.hidden_out = tf.add(tf.matmul(self.inputs_, tf.abs(self.W1)), tf.abs(self.b1))
            self.hidden_out = tf.nn.relu(self.hidden_out)

            # now calculate the hidden layer output - in this case, let's use a softmax activated
            # output layer
            self.output = tf.nn.softmax(tf.add(tf.matmul(self.hidden_out, tf.abs(self.W2)), tf.abs(self.b2)))

            # Q is our predicted Q value.
            self.Q = tf.reduce_sum(tf.multiply(self.output, self.actions_), axis=1)

            # The loss is the difference between our predicted Q_values and the Q_target
            # Sum(Qtarget - Q)^2
            self.loss = tf.reduce_mean(tf.square(self.target_Q - self.Q))

            self.optimizer = tf.train.RMSPropOptimizer(self.learning_rate).minimize(self.loss)


# Reset the graph
tf.reset_default_graph()

# Instantiate the DQNetwork
DQNetwork = DQNetwork(state_size, action_size, learning_rate)


class Memory():
    def __init__(self, max_size):
        self.buffer =[]

    def add(self, experience):
        self.buffer.append(experience)


    def sample(self, batch_size):
        buffer_size = len(self.buffer)
        index = np.random.choice(np.arange(buffer_size),
                                 #batch size instead
                                 size=buffer_size,
                                 replace=False)

        return [self.buffer[i] for i in index]

# Instantiate memory
memory = Memory(max_size = memory_size)


def predict_Qs(explore_start, explore_stop, decay_rate, decay_step, state, actions):
    ## EPSILON GREEDY STRATEGY
    # Choose action a from state s using epsilon greedy.
    ## First we randomize a number
    exp_exp_tradeoff = np.random.rand()

    # Here we'll use an improved version of our epsilon greedy strategy used in Q-learning notebook
    explore_probability = explore_stop + (explore_start - explore_stop) * np.exp(-decay_rate * decay_step)


    ###ASK HERE################################
    ###QS Value is what? when explore probability > exp_exp_tradeoff#####
    if (explore_probability > exp_exp_tradeoff):
        Qs=0

    else:
        # Get action from Q-network (exploitation)
        # Estimate the Qs values state
        Qs = sess.run(DQNetwork.output, feed_dict={DQNetwork.inputs_: state.reshape((1, state.shape))})


    return Qs, explore_probability



with tf.Session() as sess:
    # Initialize the variables
    sess.run(tf.global_variables_initializer())

    # Initialize the decay rate (that will use to reduce epsilon)
    decay_step = 0

    for episode in range(total_episodes):
        # Set step to 0
        step = 0
        # Initialize the rewards of the episode
        episode_rewards = []
        while step < max_steps:
            step += 1
            # Increase decay_step
            decay_step += 1
            # Predict the action to take and take it
            Qs_Value, explore_probability = predict_Qs(explore_start, explore_stop, decay_rate, decay_step, state,
                                                         action)
            # Get Reward from score of game
            reward=0
            # Add the reward to total reward
            episode_rewards.append(reward)
            ####TOBECHANGED################################
            next_state=[0]
            # If the game is finished
            if done:

                # Set step = max_steps to end the episode
                step = max_steps

                # Get the total reward of the episode
                total_reward = np.sum(episode_rewards)

                print('Episode: {}'.format(episode),
                      'Total reward: {}'.format(total_reward),
                      'Explore P: {:.4f}'.format(explore_probability),
                      'Training Loss {:.4f}'.format(loss))

                rewards_list.append((episode, total_reward))

                # Store transition <st,at,rt+1,st+1> in memory D
                memory.add((state, action, reward, next_state, done))

            else:
                # Add experience to memory

                memory.add((state, action, reward, next_state, done))

            ### LEARNING PART
            # Obtain random mini-batch from memory
            batch = memory.sample(batch_size)
            if batch != None:
                states_mb = np.array([each[0] for each in batch])
                actions_mb = np.array([each[1] for each in batch])
                rewards_mb = np.array([each[2] for each in batch])
                next_states_mb = np.array([each[3] for each in batch])
                dones_mb = np.array([each[4] for each in batch])
                target_Qs_batch = []

                # Get Q values for next_state
                print(next_states_mb)
                Qs_next_state = sess.run(DQNetwork.output, feed_dict={DQNetwork.inputs_: next_states_mb})

                # Set Q_target = r if the episode ends at s+1, otherwise set Q_target = r + gamma*maxQ(s', a')
                for i in range(0, len(batch)):
                    terminal = dones_mb[i]

                    # If we are in a terminal state, only equals reward
                    if terminal:
                        target_Qs_batch.append(rewards_mb[i])

                    else:
                        target = rewards_mb[i] + gamma * np.max(Qs_next_state[i])
                        target_Qs_batch.append(target)

                targets_mb = np.array([each for each in target_Qs_batch])

                loss, _ = sess.run([DQNetwork.loss, DQNetwork.optimizer],
                                   feed_dict={DQNetwork.inputs_: states_mb,
                                              DQNetwork.target_Q: targets_mb,
                                              DQNetwork.actions_: actions_mb})

