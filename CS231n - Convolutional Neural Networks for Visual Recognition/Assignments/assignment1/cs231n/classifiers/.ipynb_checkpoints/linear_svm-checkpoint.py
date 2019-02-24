import numpy as np
from random import shuffle

def svm_loss_naive(W, X, y, reg):
  """
  Structured SVM loss function, naive implementation (with loops).

  Inputs have dimension D, there are C classes, and we operate on minibatches
  of N examples.

  Inputs:
  - W: A numpy array of shape (D, C) containing weights.
  - X: A numpy array of shape (N, D) containing a minibatch of data.
  - y: A numpy array of shape (N,) containing training labels; y[i] = c means
    that X[i] has label c, where 0 <= c < C.
  - reg: (float) regularization strength

  Returns a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  dW = np.zeros(W.shape) # initialize the gradient as zero

  # compute the loss and the gradient
  num_classes = W.shape[1]
  num_train = X.shape[0]
  num_pixels = X.shape[1]
  loss = 0.0
  for i in range(num_train):
    # compute the score for ith training example 
    # by multiplying each pixel with its corresponding weight 
    # so that scores: A numpy array of shape (C, ) 
    scores = X[i].dot(W)
    # as y[i] is the correct label, scores[y[i]] is the correct class's score
    correct_class_score = scores[y[i]]
    for j in range(num_classes):
      if j == y[i]:
        continue
      # if j is not the correct class, we compute the margin according to formula
      margin = scores[j] - correct_class_score + 1 # note delta = 1
      # we add loss += max(0, margin)
      if margin > 0:
        loss += margin
        # reference from: https://cs231n.github.io/optimization-1/#analytic
        
        # sum over all training examples 
        dW[:,y[i]] -= X[i,:].T
        dW[:,j] += X[i,:].T
    
  # Right now the loss is a sum over all training examples, but we want it
  # to be an average instead so we divide by num_train.
  loss /= num_train

  # Add regularization to the loss.
  loss += reg * np.sum(W * W)

  # divide the gradient of weights by the number of training examples 
  dW /= num_train

  # add the regularization term to the gradient of weights 
  dW += reg*W

  #############################################################################
  # TODO:                                                                     #
  # Compute the gradient of the loss function and store it dW.                #
  # Rather that first computing the loss and then computing the derivative,   #
  # it may be simpler to compute the derivative at the same time that the     #
  # loss is being computed. As a result you may need to modify some of the    #
  # code above to compute the gradient.                                       #
  #############################################################################


  return loss, dW


def svm_loss_vectorized(W, X, y, reg):
  """
  Structured SVM loss function, vectorized implementation.

  Inputs and outputs are the same as svm_loss_naive.
  """
  loss = 0.0
  dW = np.zeros(W.shape) # initialize the gradient as zero
  #############################################################################
  # TODO:                                                                     #
  # Implement a vectorized version of the structured SVM loss, storing the    #
  # result in loss.                                                           #
  #############################################################################
  #############################################################################
  #                             END OF YOUR CODE                              #
  #############################################################################
  num_train = X.shape[0]
  # scores: a numpy array of shape (N, C) containing scores for all training examples 
  scores = X.dot(W) 
    
  # correct_class_score: a numpy array of shape (N, ) mapping from ith training example to ith correct training label's score 
  # np.arange(num_train): array([0, 1, 2, ..., num_train])
  # y: a numpy array of shape (N, ) containing correct training labels 
  correct_class_score = scores[np.arange(num_train), y].reshape(-1, 1)

  # calculate the margins' score according to formula 
  margins = np.maximum(0, scores - correct_class_score + 1)
    
  # set correct training labels' margins to 0
  margins[np.arange(num_train), y] = 0 
  
  # compute the average so we divide by num_train 
  loss /= num_train

  # add regularization term to the loss
  loss += reg * np.sum(W * W)

  #############################################################################
  # TODO:                                                                     #
  # Implement a vectorized version of the gradient for the structured SVM     #
  # loss, storing the result in dW.                                           #
  #                                                                           #
  # Hint: Instead of computing the gradient from scratch, it may be easier    #
  # to reuse some of the intermediate values that you used to compute the     #
  # loss.                                                                     #
  #############################################################################
  
  # 
  margins[margins > 0] = 1
    
  margins[np.arange(num_train), y] = -np.sum(margins, axis=1)

  dW = X.T.dot(margins)
 
  # divide the number of training examples 
  dW /= num_train
    
  # add regularization term to the gradient
  dW += reg*W
  #############################################################################
  #                             END OF YOUR CODE                              #
  #############################################################################

  return loss, dW
