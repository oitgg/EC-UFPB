import React from 'react';
import { Link } from 'react-router';
import '../styles/NotFoundPage.css';

const NotFoundPage = (props) => {
  return (
    <div className="NotFoundPage__container container">
      <h2 className="NotFoundPage__heading">Desculpe, a página não está desponível.</h2>
      <p className="NotFoundPage__message">
        O link solicitado pode estar quebrado ou a página pode ter sido removida.<Link to="/">Voltar para a página inicial.</Link>
      </p>
    </div>
  );
}

export default NotFoundPage;
