import React from 'react';
import { reduxForm } from 'redux-form';
import { userSignUp } from '../actions';
import { getAuthErrors, getIsAuthenticating } from '../store/rootReducer';
import ErrorMessages from '../components/ErrorMessages';
import '../styles/SignUpForm.css';

class SignUpForm extends React.Component {
  renderError(field) {
    if (field.touched && field.error) {
      return (
        <span className="SignUpForm__error-text">
          {field.error}
        </span>
      );
    }
  }

  render() {
    const {
      fields: { email, username, password },
      handleSubmit,
      userSignUp,
      isAuthenticating
    } = this.props;
    return (
      <form className="SignUpForm__root" onSubmit={handleSubmit(userSignUp)}>
        <fieldset>
          <input
            type="email"
            placeholder="Email"
            className="SignUpForm__input"
            {...email}
          />
          {this.renderError(email)}
        </fieldset>
        <fieldset>
          <input
            type="text"
            placeholder="Usuário"
            className="SignUpForm__input"
            {...username}
          />
          {this.renderError(username)}
        </fieldset>
        <fieldset>
          <input
            type="password"
            placeholder="Criar senha"
            className="SignUpForm__input"
            {...password}
          />
          {this.renderError(password)}
        </fieldset>
        <button
          className="SignUpForm__button"
          disabled={this.props.invalid || isAuthenticating}
          type="submit">
          {isAuthenticating ?
          <i className="fa fa-spinner fa-pulse fa-3x fa-fw SignUpForm__spinner" /> :
          'Sign Up'}
        </button>
        <ErrorMessages messages={this.props.errorMessages} />
      </form>
    );
  }
}

const validate = (values) => {
  const errors = {};
  if (!values.email) {
    errors.email = 'Email is required';
  } else if (!/^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}$/i.test(values.email)) {
    errors.email = 'Invalid email address';
  }

  if (!values.username) {
    errors.username = 'Usuário é necessário';
  } else if (values.username.length < 4) {
    errors.username = 'Usuário muito curto (mínimo 3 caracteres)';
  } else if (values.username.length > 30) {
    errors.username = 'Usuário muito longo (máximo 30 caracteres)';
  } else if (!/^[A-Z0-9_-]{3,30}$/i.test(values.username)) {
     errors.username = 'Usuário deve ser uma única palavra (- e _ permitidos)'
  } // Add uniqueness

  if (!values.password) {
    errors.password = 'Senha é necessária';
  } else if (values.password.length < 8) {
    errors.password = 'Senha muito curta (mínimo 8 caracteres)';
  }

  return errors;
}

const mapStateToProps = (state) => ({
  errorMessages: getAuthErrors(state),
  isAuthenticating: getIsAuthenticating(state),
});

export default reduxForm({
  form: 'SignUp',
  fields: ['email', 'username', 'password'],
  validate,
}, mapStateToProps, { userSignUp })(SignUpForm);
