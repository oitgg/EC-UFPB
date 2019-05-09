import defaultAvatarImg from '../images/default-avatar.png';
import noImage from '../images/no-image.jpg';

// Função helper p/ avatar do usuário
export const getAvatarUrl = (avatarUrl) => {
  const facebookAvatarUrl = /http:\/\/graph.facebook.com\//;
  return avatarUrl ?
  `${(process.env.NODE_ENV !== 'production' && !facebookAvatarUrl.test(avatarUrl)) ? 'http://localhost:5000' : ''}${avatarUrl}` :
  defaultAvatarImg;
}

// Função helper p/ postar imagem
export const getImageUrl = (imageUrl) => {
  return imageUrl ? `${process.env.NODE_ENV !== 'production' ? 'http://localhost:5000' : ''}${imageUrl}` : noImage;
}

// Função helper p/ pluralização
export const pluralize = (count, singular, plural) => {
  return count === 1 ? singular : plural;
}

// Mensagens de notificação
export const getNotificationMessage = (type, username) => {
  switch (type) {
    case 'START_FOLLOWING':
      return `${username} começou a te seguir`;
    case 'LIKE_POST':
      return `${username} curtiu seu post`;
    case 'COMMENT_ON_POST':
      return `${username} comentuo no seu post`;
    default:
      return null;
    }
}
