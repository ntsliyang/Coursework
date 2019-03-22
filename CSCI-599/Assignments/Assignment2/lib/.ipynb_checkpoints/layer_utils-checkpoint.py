import numpy as np


def sigmoid(x):
    """
    A numerically stable version of the logistic sigmoid function.
    """
    pos_mask = (x >= 0)
    neg_mask = (x < 0)
    z = np.zeros_like(x)
    z[pos_mask] = np.exp(-x[pos_mask])
    z[neg_mask] = np.exp(x[neg_mask])
    top = np.ones_like(x)
    top[neg_mask] = z[neg_mask]
    return top / (1 + z)


class RNN(object):
    def __init__(self, *args):
        """
        RNN Object to serialize the NN layers
        Please read this code block and understand how it works
        """
        self.params = {}
        self.grads = {}
        self.layers = []
        self.paramName2Indices = {}
        self.layer_names = {}

        # process the parameters layer by layer
        layer_cnt = 0
        for layer in args:
            for n, v in layer.params.items():
                if v is None:
                    continue
                self.params[n] = v
                self.paramName2Indices[n] = layer_cnt
            for n, v in layer.grads.items():
                self.grads[n] = v
            if layer.name in self.layer_names:
                raise ValueError("Existing name {}!".format(layer.name))
            self.layer_names[layer.name] = True
            self.layers.append(layer)
            layer_cnt += 1
        layer_cnt = 0

    def assign(self, name, val):
        # load the given values to the layer by name
        layer_cnt = self.paramName2Indices[name]
        self.layers[layer_cnt].params[name] = val

    def assign_grads(self, name, val):
        # load the given values to the layer by name
        layer_cnt = self.paramName2Indices[name]
        self.layers[layer_cnt].grads[name] = val

    def get_params(self, name):
        # return the parameters by name
        return self.params[name]

    def get_grads(self, name):
        # return the gradients by name
        return self.grads[name]

    def gather_params(self):
        """
        Collect the parameters of every submodules
        """
        for layer in self.layers:
            for n, v in layer.params.iteritems():
                self.params[n] = v

    def gather_grads(self):
        """
        Collect the gradients of every submodules
        """
        for layer in self.layers:
            for n, v in layer.grads.iteritems():
                self.grads[n] = v

    def load(self, pretrained):
        """ 
        Load a pretrained model by names 
        """
        for layer in self.layers:
            if not hasattr(layer, "params"):
                continue
            for n, v in layer.params.iteritems():
                if n in pretrained.keys():
                    layer.params[n] = pretrained[n].copy()
                    print("Loading Params: {} Shape: {}".format(n, layer.params[n].shape))


class VanillaRNN(object):
    def __init__(self, input_dim, h_dim, init_scale=0.02, name='vanilla_rnn'):
        """
        In forward pass, please use self.params for the weights and biases for this layer
        In backward pass, store the computed gradients to self.grads
        - name: the name of current layer
        - input_dim: input dimension
        - h_dim: hidden state dimension
        - meta: to store the forward pass activations for computing backpropagation 
        """
        self.name = name
        self.wx_name = name + "_wx"
        self.wh_name = name + "_wh"
        self.b_name = name + "_b"
        self.input_dim = input_dim
        self.h_dim = h_dim
        self.params = {}
        self.grads = {}
        self.params[self.wx_name] = init_scale * np.random.randn(input_dim, h_dim)
        self.params[self.wh_name] = init_scale * np.random.randn(h_dim, h_dim)
        self.params[self.b_name] = np.zeros(h_dim)
        self.grads[self.wx_name] = None
        self.grads[self.wh_name] = None
        self.grads[self.b_name] = None
        self.meta = None
        
    def step_forward(self, x, prev_h):
        """
        x: input feature (N, D)
        prev_h: hidden state from the previous timestep (N, H)

        meta: variables needed for the backward pass
        """
        next_h, meta = None, None
        assert np.prod(x.shape[1:]) == self.input_dim, "But got {} and {}".format(
            np.prod(x.shape[1:]), self.input_dim)
        ############################################################################
        # TODO: implement forward pass of a single timestep of a vanilla RNN.      #
        # Store the results in the variable output provided above as well as       #
        # values needed for the backward pass.                                     #
        ############################################################################
        Wh = self.params[self.wh_name]
        Wx = self.params[self.wx_name]
        b = self.params[self.b_name]
        next_h = np.tanh(np.dot(prev_h, Wh) + np.dot(x, Wx) + b)
        meta = {"prev_h": prev_h, "x": x}
        #############################################################################
        #                             END OF YOUR CODE                              #
        #############################################################################
        return next_h, meta

    def step_backward(self, dnext_h, meta):
        """
        dnext_h: gradient w.r.t. next hidden state
        meta: variables needed for the backward pass

        dx: gradients of input feature (N, D)
        dprev_h: gradients of previous hiddel state (N, H)
        dWh: gradients w.r.t. feature-to-hidden weights (D, H)
        dWx: gradients w.r.t. hidden-to-hidden weights (H, H)
        db: gradients w.r.t bias (H,)
        """
        dx, dprev_h, dWx, dWh, db = None, None, None, None, None
        #############################################################################
        # TODO: Implement the backward pass of a single timestep of a vanilla RNN.  #
        # Store the computed gradients for current layer in self.grads with         #
        # corresponding name.                                                       # 
        #############################################################################
        Wh, Wx, prev_h, x, b = self.params[self.wh_name], self.params[self.wx_name], meta['prev_h'], meta['x'], self.params[self.b_name]
        next_h = np.tanh(np.dot(prev_h, Wh) + np.dot(x, Wx) + b)
        dx = np.dot(dnext_h *(1 - np.square(next_h)), Wx.T)
        dprev_h = np.dot(dnext_h * (1 - np.square(next_h)), Wh.T)
        dWx = np.dot(x.T, dnext_h * (1 - np.square(next_h)))
        dWh = np.dot(prev_h.T, dnext_h * (1 - np.square(next_h)))
        db = np.sum(dnext_h * (1 - np.square(next_h)), axis=0)
        # self.grads[self.wx_name], self.grads[self.wh_name], self.grads[self.b_name] = dWx, dWh, db
        #############################################################################
        #                             END OF YOUR CODE                              #
        #############################################################################
        return dx, dprev_h, dWx, dWh, db

    def forward(self, x, h0):
        """
        x: input feature for the entire timeseries (N, T, D)
        h0: initial hidden state (N, H)
        """
        h = None
        self.meta = []
        ##############################################################################
        # TODO: Implement forward pass for a vanilla RNN running on a sequence of    #
        # input data. You should use the step_forward function that you defined      #
        # above. You can use a for loop to help compute the forward pass.            #
        ##############################################################################
        N = x.shape[0] # number of training examples 
        T = x.shape[1] # number of time steps
        H = self.params[self.wh_name].shape[0]
        h, self.meta = np.zeros((N, T+1, H)), [0]*T

        # Initialize hidden layer
        h[:,0,:] = h0

        for i in range(T):
            h[:,i+1,:], self.meta[i] = self.step_forward(x[:,i,:], h[:,i,:])

        # Remove initial hidden state
        h = h[:,1:,:]
        ##############################################################################
        #                               END OF YOUR CODE                             #
        ##############################################################################
        return h

    def backward(self, dh):
        """
        dh: gradients of hidden states for the entire timeseries (N, T, H)

        dx: gradient of inputs (N, T, D)
        dh0: gradient w.r.t. initial hidden state (N, H)
        self.grads[self.wx_name]: gradient of input-to-hidden weights (D, H)
        self.grads[self.wh_name]: gradient of hidden-to-hidden weights (H, H)
        self.grads[self.b_name]: gradient of biases (H,)
        """
        dx, dh0 = None, None
        self.grads[self.wx_name] = None
        self.grads[self.wh_name] = None
        self.grads[self.b_name] = None
        ##############################################################################
        # TODO: Implement the backward pass for a vanilla RNN running an entire      #
        # sequence of data. You should use the rnn_step_backward function that you   #
        # defined above. You can use a for loop to help compute the backward pass.   #
        # HINT: Gradients of hidden states come from two sources                     #
        ##############################################################################
        N = dh.shape[0]
        T = dh.shape[1]
        H = dh.shape[2]
        D = self.params[self.wx_name].shape[0]
        
        # initialize gradients
        dx = np.zeros((N, T, D))
        dh0 = np.zeros((N, H))
        self.grads[self.wx_name] = np.zeros((D, H))
        self.grads[self.wh_name] = np.zeros((H, H))
        self.grads[self.b_name] = np.zeros((H, ))
        
        # initialize current hidden state
        dh_t = np.zeros((N, H))
        
        # compute gradients
        for i in range(T): 
            dh_current = dh[:, T - i - 1, :] + dh_t
            dx_t, dh_t, dWx_t, dWh_t, db_t = self.step_backward(dh_current, self.meta[T - i - 1])
            
            # accumulate the gradients but not the hidden state 
            dx[:,T - i - 1,:] += dx_t
            self.grads[self.wx_name] += dWx_t
            self.grads[self.wh_name] += dWh_t
            self.grads[self.b_name] += db_t
        
        dh0 += dh_t
        ##############################################################################
        #                               END OF YOUR CODE                             #
        ##############################################################################
        self.meta = []
        return dx, dh0


class LSTM(object):
    def __init__(self, input_dim, h_dim, init_scale=0.02, name='lstm'):
        """
        In forward pass, please use self.params for the weights and biases for this layer
        In backward pass, store the computed gradients to self.grads
        - name: the name of current layer
        - input_dim: input dimension
        - h_dim: hidden state dimension
        - meta: to store the forward pass activations for computing backpropagation 
        """
        self.name = name
        self.wx_name = name + "_wx"
        self.wh_name = name + "_wh"
        self.b_name = name + "_b"
        self.input_dim = input_dim
        self.h_dim = h_dim
        self.params = {}
        self.grads = {}
        self.params[self.wx_name] = init_scale * np.random.randn(input_dim, 4*h_dim)
        self.params[self.wh_name] = init_scale * np.random.randn(h_dim, 4*h_dim)
        self.params[self.b_name] = np.zeros(4*h_dim)
        self.grads[self.wx_name] = None
        self.grads[self.wh_name] = None
        self.grads[self.b_name] = None
        self.meta = None
        
    def step_forward(self, x, prev_h, prev_c):
        """
        x: input feature (N, D)
        prev_h: hidden state from the previous timestep (N, H)

        meta: variables needed for the backward pass
        """
        next_h, next_c, meta = None, None, None
        #############################################################################
        # TODO: Implement the forward pass for a single timestep of an LSTM.        #
        # You may want to use the numerically stable sigmoid implementation above.  #
        #############################################################################
        Wh = self.params[self.wh_name]
        Wx = self.params[self.wx_name]
        b = self.params[self.b_name]
        H = Wh.shape[1]
        
        # print (prev_h.shape, Wh.shape, x.shape, Wx.shape, b.shape)
        temp = np.dot(prev_h, Wh) + np.dot(x, Wx) + b
        # print (np.dot(prev_h, Wh[:,H:2*H]) + np.dot(x, Wx[:,H:2*H]) + b[H:2*H] == np.split(temp, 4, axis=1)[1])
        i, f, o, g = sigmoid(np.split(temp, 4, axis=1)[0]), sigmoid(np.split(temp, 4, axis=1)[1]), sigmoid(np.split(temp, 4, axis=1)[2]), np.tanh(np.split(temp, 4, axis=1)[3])
        next_c = np.add(np.multiply(f, prev_c), np.multiply(i,g))
        next_h = np.multiply(o, np.tanh(next_c))
        meta = {'prev_h': prev_h, 'prev_c': prev_c, 'x': x, 'next_h': next_h, 'next_c': next_c, 'i': i, 'f': f, 'o': o, 'g': g}
        #############################################################################
        #                               END OF YOUR CODE                            #
        #############################################################################
        return next_h, next_c, meta
        
    def step_backward(self, dnext_h, dnext_c, meta):
        """
        dnext_h: gradient w.r.t. next hidden state
        meta: variables needed for the backward pass

        dx: gradients of input feature (N, D)
        dprev_h: gradients of previous hiddel state (N, H)
        dWh: gradients w.r.t. feature-to-hidden weights (D, H)
        dWx: gradients w.r.t. hidden-to-hidden weights (H, H)
        db: gradients w.r.t bias (H,)
        """
        dx, dh, dc, dWx, dWh, db = None, None, None, None, None, None
        #############################################################################
        # TODO: Implement the backward pass for a single timestep of an LSTM.       #
        #                                                                           #
        # HINT: For sigmoid and tanh you can compute local derivatives in terms of  #
        # the output value from the nonlinearity.                                   #
        #############################################################################
        prev_h, prev_c, next_h, next_c, x, i, f, o, g = meta['prev_h'], meta['prev_c'], meta['next_h'], meta['next_c'], meta['x'], meta['i'], meta['f'], meta['o'], meta['g']
        dnext_c += dnext_h * o * (1 - np.square(np.tanh(next_c)))
        do = dnext_h * np.tanh(next_c)
        df = dnext_c * prev_c 
        di = dnext_c * g
        dg = dnext_c * i 
        
        N = prev_h.shape[0]
        H = prev_h.shape[1]
        da = np.zeros((N, 4*H))
        da[:, 0:H] = di * i * (1 - i)
        da[:, H:2*H] = df * f * (1 - f)
        da[:, 2*H:3*H] = do * o * (1 - o)
        da[:, 3*H:] = dg * (1 - g ** 2)
        
        Wx, Wh = self.params[self.wx_name], self.params[self.wh_name]
        dx = np.dot(da, Wx.T)
        dprev_h = np.dot(da, Wh.T)
        dprev_c = np.multiply(dnext_c, f)
        dWx = np.dot(x.T, da)
        dWh = np.dot(prev_h.T, da)
        db = np.sum(da, axis=0)
        #############################################################################
        #                               END OF YOUR CODE                            #
        #############################################################################

        return dx, dprev_h, dprev_c, dWx, dWh, db

    def forward(self, x, h0):
        """
        Forward pass for an LSTM over an entire sequence of data. We assume an input
        sequence composed of T vectors, each of dimension D. The LSTM uses a hidden
        size of H, and we work over a minibatch containing N sequences. After running
        the LSTM forward, we return the hidden states for all timesteps.

        Note that the initial cell state is passed as input, but the initial cell
        state is set to zero. Also note that the cell state is not returned; it is
        an internal variable to the LSTM and is not accessed from outside.

        Inputs:
        - x: Input data of shape (N, T, D)
        - h0: Initial hidden state of shape (N, H)
        - Wx: Weights for input-to-hidden connections, of shape (D, 4H)
        - Wh: Weights for hidden-to-hidden connections, of shape (H, 4H)
        - b: Biases of shape (4H,)

        Returns a tuple of:
        - h: Hidden states for all timesteps of all sequences, of shape (N, T, H)
        - cache: Values needed for the backward pass.
        """
        h = None
        self.meta = []
        #############################################################################
        # TODO: Implement the forward pass for an LSTM over an entire timeseries.   #
        # You should use the lstm_step_forward function that you just defined.      #
        #############################################################################
        N = x.shape[0] # number of training examples 
        T = x.shape[1] # number of time steps
        H = self.params[self.wh_name].shape[0]
        h, c, self.meta = np.zeros((N, T+1, H)), np.zeros((N, T + 1, H)), [0]*T

        # Initialize hidden layer
        h[:,0,:] = h0
        
        for i in range(T):
            h[:,i+1,:], c[:,i+1,:], self.meta[i] = self.step_forward(x[:,i,:], h[:,i,:], c[:,i,:])

        # Remove initial hidden state
        h = h[:,1:,:]
        c = c[:,1:,:]
        
        #############################################################################
        #                               END OF YOUR CODE                            #
        #############################################################################
        return h

    def backward(self, dh):
        """
        Backward pass for an LSTM over an entire sequence of data.]

        Inputs:
        - dh: Upstream gradients of hidden states, of shape (N, T, H)
        - cache: Values from the forward pass

        Returns a tuple of:
        - dx: Gradient of input data of shape (N, T, D)
        - dh0: Gradient of initial hidden state of shape (N, H)
        - dWx: Gradient of input-to-hidden weight matrix of shape (D, 4H)
        - dWh: Gradient of hidden-to-hidden weight matrix of shape (H, 4H)
        - db: Gradient of biases, of shape (4H,)
        """
        dx, dh0 = None, None
        #############################################################################
        # TODO: Implement the backward pass for an LSTM over an entire timeseries.  #
        # You should use the lstm_step_backward function that you just defined.     #
        #############################################################################
        N = dh.shape[0]
        T = dh.shape[1]
        H = dh.shape[2]
        D = self.params[self.wx_name].shape[0]
        
        # initialize gradients
        dx = np.zeros((N, T, D))
        dh0 = np.zeros((N, H))
        self.grads[self.wx_name] = np.zeros((D, 4*H))
        self.grads[self.wh_name] = np.zeros((H, 4*H))
        self.grads[self.b_name] = np.zeros((4*H, ))
        
        # initialize current hidden state
        dprev_h_t = np.zeros((N, H))
        dprev_c = np.zeros((N, H))
        
        # compute gradients
        for i in range(T): 
            # {'prev_h': prev_h, 'prev_c': prev_c, 'x': x, 'next_h': next_h, 'next_c': next_c, 'i': i, 'f': f, 'o': o, 'g': g}
            dh_current = dh[:,T - i - 1,:] + dprev_h_t
            dx_t, dprev_h_t, dprev_c, dWx_t, dWh_t, db_t = self.step_backward(dh_current, dprev_c, self.meta[T - i - 1])
            
            # accumulate the gradients but not the hidden state 
            dx[:,T - i - 1,:] += dx_t
            self.grads[self.wx_name] += dWx_t
            self.grads[self.wh_name] += dWh_t
            self.grads[self.b_name] += db_t
        
        dh0 += dprev_h_t
        #############################################################################
        #                               END OF YOUR CODE                            #
        #############################################################################
        self.meta = []
        return dx, dh0
            
        
class word_embedding(object):
    def __init__(self, voc_dim, vec_dim, name="we"):
        """
        In forward pass, please use self.params for the weights and biases for this layer
        In backward pass, store the computed gradients to self.grads
        - name: the name of current layer
        - v_dim: words size
        - output_dim: vector dimension
        - meta: to store the forward pass activations for computing backpropagation
        """
        self.name = name
        self.w_name = name + "_w"
        self.voc_dim = voc_dim
        self.vec_dim = vec_dim
        self.params = {}
        self.grads = {}
        self.params[self.w_name] = np.random.randn(voc_dim, vec_dim)
        self.grads[self.w_name] = None
        self.meta = None
        
    def forward(self, x):
        """
        Forward pass for word embeddings. We operate on minibatches of size N where
        each sequence has length T. We assume a vocabulary of V words, assigning each
        to a vector of dimension D.

        Inputs:
        - x: Integer array of shape (N, T) giving indices of words. Each element idx
          of x muxt be in the range 0 <= idx < V.
        - W: Weight matrix of shape (V, D) giving word vectors for all words.

        Returns a tuple of:
        - out: Array of shape (N, T, D) giving word vectors for all input words.
        - meta: Values needed for the backward pass
        """
        out, self.meta = None, None
        ##############################################################################
        # TODO: Implement the forward pass for word embeddings.                      #
        #                                                                            #
        # HINT: This can be done in one line using NumPy's array indexing.           #
        ##############################################################################
        
        # define variables
        W = self.params[self.w_name]
        out = W[x,:]
        self.meta = W, x
        ##############################################################################
        #                               END OF YOUR CODE                             #
        ##############################################################################
        return out
        
    def backward(self, dout):
        """
        Backward pass for word embeddings. We cannot back-propagate into the words
        since they are integers, so we only return gradient for the word embedding
        matrix.

        HINT: Look up the function np.add.at

        Inputs:
        - dout: Upstream gradients of shape (N, T, D)
        - cache: Values from the forward pass

        Returns:
        - dW: Gradient of word embedding matrix, of shape (V, D).
        """
        self.grads[self.w_name] = None
        ##############################################################################
        # TODO: Implement the backward pass for word embeddings.                     #
        # Note that Words can appear more than once in a sequence.                   #
        # HINT: Look up the function np.add.at                                       #
        ##############################################################################
        W, x = self.meta 
        V, D = self.params[self.w_name].shape
        self.grads[self.w_name] = np.zeros((V, D))
        np.add.at(self.grads[self.w_name], x, dout)
        ##############################################################################
        #                               END OF YOUR CODE                             #
        ##############################################################################


class temporal_fc(object):
    def __init__(self, input_dim, output_dim, init_scale=0.02, name='t_fc'):
        """
        In forward pass, please use self.params for the weights and biases for this layer
        In backward pass, store the computed gradients to self.grads
        - name: the name of current layer
        - input_dim: input dimension
        - output_dim: output dimension
        - meta: to store the forward pass activations for computing backpropagation 
        """
        self.name = name
        self.w_name = name + "_w"
        self.b_name = name + "_b"
        self.input_dim = input_dim
        self.output_dim = output_dim
        self.params = {}
        self.grads = {}
        self.params[self.w_name] = init_scale * np.random.randn(input_dim, output_dim)
        self.params[self.b_name] = np.zeros(output_dim)
        self.grads[self.w_name] = None
        self.grads[self.b_name] = None
        self.meta = None
        
    def forward(self, x):
        """
        Forward pass for a temporal fc layer. The input is a set of D-dimensional
        vectors arranged into a minibatch of N timeseries, each of length T. We use
        an affine function to transform each of those vectors into a new vector of
        dimension M.

        Inputs:
        - x: Input data of shape (N, T, D)
        - w: Weights of shape (D, M)
        - b: Biases of shape (M,)

        Returns a tuple of:
        - out: Output data of shape (N, T, M)
        - cache: Values needed for the backward pass
        """
        N, T, D = x.shape
        M = self.params[self.b_name].shape[0]
        out = x.reshape(N * T, D).dot(self.params[self.w_name]).reshape(N, T, M) + self.params[self.b_name]
        self.meta = [x, out]
        return out

    def backward(self, dout):
        """
        Backward pass for temporal fc layer.

        Input:
        - dout: Upstream gradients of shape (N, T, M)
        - cache: Values from forward pass

        Returns a tuple of:
        - dx: Gradient of input, of shape (N, T, D)
        - dw: Gradient of weights, of shape (D, M)
        - db: Gradient of biases, of shape (M,)
        """
        x, out = self.meta
        N, T, D = x.shape
        M = self.params[self.b_name].shape[0]

        dx = dout.reshape(N * T, M).dot(self.params[self.w_name].T).reshape(N, T, D)
        self.grads[self.w_name] = dout.reshape(N * T, M).T.dot(x.reshape(N * T, D)).T
        self.grads[self.b_name] = dout.sum(axis=(0, 1))

        return dx


class temporal_softmax_loss(object):
    def __init__(self, dim_average=True):
        """
        - dim_average: if dividing by the input dimension or not
        - dLoss: intermediate variables to store the scores
        - label: Ground truth label for classification task
        """
        self.dim_average = dim_average  # if average w.r.t. the total number of features
        self.dLoss = None
        self.label = None

    def forward(self, feat, label, mask):
        """ Some comments """
        loss = None
        N, T, V = feat.shape

        feat_flat = feat.reshape(N * T, V)
        label_flat = label.reshape(N * T)
        mask_flat = mask.reshape(N * T)

        probs = np.exp(feat_flat - np.max(feat_flat, axis=1, keepdims=True))
        probs /= np.sum(probs, axis=1, keepdims=True)
        loss = -np.sum(mask_flat * np.log(probs[np.arange(N * T), label_flat]))
        if self.dim_average:
            loss /= N

        self.dLoss = probs.copy()
        self.label = label
        self.mask = mask
        
        return loss

    def backward(self):
        N, T = self.label.shape
        dLoss = self.dLoss
        if dLoss is None:
            raise ValueError("No forward function called before for this module!")
        dLoss[np.arange(dLoss.shape[0]), self.label.reshape(N * T)] -= 1.0
        if self.dim_average:
            dLoss /= N
        dLoss *= self.mask.reshape(N * T)[:, None]
        self.dLoss = dLoss
        
        return dLoss.reshape(N, T, -1)
