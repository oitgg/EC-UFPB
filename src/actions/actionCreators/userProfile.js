import axios from 'axios';
import { API_URL } from '../../config/constants';
import {
  PROFILE_UPDATE_SUCCESS,
  PROFILE_UPDATE_FAILURE
} from '../actionTypes';
import { getAuthToken, getCurrentUser } from '../../store/rootReducer';
import { push } from 'react-router-redux';

export const userUpdate = ({ username, email }, file) => (dispatch, getState) => {
  const authToken = getAuthToken(getState());

  let formData = new FormData();
  if (file) {
    formData.append('avatar', file);
  }
  formData.append('username', username);
  formData.append('email', email);

  return axios({
    method: 'patch',
    url: `${API_URL}/me`,
    data: formData,
    headers: {
      'Authorization': `Token ${authToken}`
    }
  })
  .then(({data}) => {
    console.log('atualização com sucesso', data);
    dispatch({
      type: PROFILE_UPDATE_SUCCESS,
      payload: data.user,
    });
    const currentUser = getCurrentUser(getState());
    dispatch(push(`/${currentUser.username}`));
  })
  .catch(response => {
    console.log('atualização sem sucesso', response);
    dispatch({
      type: PROFILE_UPDATE_FAILURE,
    });
  });
}
