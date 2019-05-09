import React from 'react';
import '../styles/FollowButton.css';

const FollowButton = (props) => {
  if (props.isFollowing) {
    return (
      <button
        className="FollowButton__root FollowButton--following"
        onClick={props.onUnfollowClick}>
        Seguindo
      </button>
    )
  } else {
    return (
      <button
        className="FollowButton__root"
        onClick={props.onFollowClick}>
        Seguir
      </button>
    )
  }
}

export default FollowButton;
