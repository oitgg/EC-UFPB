import axios from 'axios';
import { getAuthToken } from '../../store/rootReducer';
import { API_URL } from '../../config/constants';
import {
  ADD_COMMENT,
  DELETE_COMMENT,
} from '../actionTypes';

export const addComment = (postId, commentBody) => (dispatch, getState) => {
  const authToken = getAuthToken(getState());

  return axios({
    method: 'post',
    url: `${API_URL}/posts/${postId}/comments`,
    headers: {
      'Authorization': `Token ${authToken}`,
    },
    data: {
      body: commentBody
    },
  })
  .then(({data}) => {
    console.log('comentário criado com sucesso', data);
    dispatch({
      type: ADD_COMMENT,
      payload: data.comment,
      postId,
    })
  })
  .catch(response => {
    console.log('comentário não foi criado', response);
  });
}

export const deleteComment = (postId, commentId) => (dispatch, getState) => {
  const authToken = getAuthToken(getState());

  return axios({
    method: 'delete',
    url: `${API_URL}/posts/${postId}/comments/${commentId}`,
    headers: {
      'Authorization': `Token ${authToken}`,
    },
  })
  .then(() => {
    console.log('comentário excluído com sucesso');
    dispatch({
      type: DELETE_COMMENT,
      postId,
      commentId,
    });
  }, (error) => {
    console.log('comentário não excluído', error);
  });
}
