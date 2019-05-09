import axios from 'axios';
import { API_URL } from '../../config/constants';
import { getAuthToken } from '../../store/rootReducer';
import {
  FETCH_FOLLOW_SUGGESTIONS_START,
  FETCH_FOLLOW_SUGGESTIONS_SUCCESS,
  FETCH_FOLLOW_SUGGESTIONS_FAILURE,
} from '../actionTypes';

export const fetchFollowSuggestions = () => (dispatch, getState) => {
  dispatch({type: FETCH_FOLLOW_SUGGESTIONS_START});

  const authToken = getAuthToken(getState());

  return axios({
    method: 'get',
    url: `${API_URL}/follow_suggestions`,
    headers: {
      'Authorization': `Token ${authToken}`
    }
  })
  .then(({data}) => {
    console.log('sugestões capturadas com sucesso', data);
    dispatch({
      type: FETCH_FOLLOW_SUGGESTIONS_SUCCESS,
      payload: data.users,
    });
  }, (error) => {
    console.log('sugestões não capturadas', error);
    dispatch({
      type: FETCH_FOLLOW_SUGGESTIONS_FAILURE,
    });
  });
}
