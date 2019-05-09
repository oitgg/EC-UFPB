CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) UNIQUE NOT NULL,
  `firstname` varchar(155) NOT NULL,
  `surname` varchar(155) NOT NULL,
  `password` varchar(255) NOT NULL, 
  `bio` varchar(600) DEFAULT NULL,
  `type` enum('public','private') NOT NULL DEFAULT 'public',
  PRIMARY KEY(`id`, `username`)
);

CREATE TABLE `post` (
  `post_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `image_url` varchar(255) NOT NULL,
  `description` varchar(255),
  `time` datetime NOT NULL DEFAULT NOW(),
  FOREIGN KEY(`user_id`) REFERENCES users(`id`) ON DELETE CASCADE,
  PRIMARY KEY(`post_id`, `user_id`)
);

CREATE TABLE `comments` (
  `comment_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `content` mediumtext NOT NULL,
  `post_id` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),  
  FOREIGN KEY (`post_id`) REFERENCES post(`post_id`) ON DELETE CASCADE,
  FOREIGN KEY (`user_id`) REFERENCES users(`id`) ON DELETE CASCADE,
  PRIMARY KEY(`comment_id`, `user_id`)
);

CREATE TABLE `likes` (
  `like_id` int(11) NOT NULL AUTO_INCREMENT,
  `like_by` int(11) NOT NULL,
  `post_id` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  FOREIGN KEY(`like_by`) REFERENCES users(`id`) ON DELETE CASCADE,
  FOREIGN KEY(`post_id`) REFERENCES post(`post_id`) ON DELETE CASCADE,
  PRIMARY KEY(`like_id`, `like_by`, `post_id`) 
);


CREATE TABLE `hashtag` (
  `hashtag_id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `hashtag_name` varchar(255) NOT NULL,
  `src_post` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  `type_src` enum('post', 'comment') NOT NULL,
  FOREIGN KEY(`user_id`) REFERENCES post(`user_id`) ON DELETE CASCADE,
  FOREIGN KEY(`src_post`) REFERENCES post(`post_id`) ON DELETE CASCADE
);

CREATE TABLE `photo_tag` (
  `photo_id` int(11) NOT NULL,
  `who_tag` varchar(255) NOT NULL,
  FOREIGN KEY(`photo_id`) REFERENCES post(`post_id`) ON DELETE CASCADE,
  FOREIGN KEY(`who_tag`) REFERENCES users(`username`) ON DELETE CASCADE,
  PRIMARY KEY(`photo_id`, `who_tag`)
);

CREATE TABLE `follow_system` (
  `follow_id` int(11) NOT NULL AUTO_INCREMENT,
  `follower_id` int(11) NOT NULL,
  `followee_id` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  `status` enum('accepted', 'pending') NOT NULL DEFAULT 'accepted',
  FOREIGN KEY(`follower_id`) REFERENCES users(`id`) ON DELETE CASCADE,
  FOREIGN KEY(`followee_id`) REFERENCES users(`id`) ON DELETE CASCADE,
  PRIMARY KEY(`follow_id`, `follower_id`, `followee_id`)
);

CREATE TABLE `message` (
  `message_id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,  
  `msg_by` int(11) NOT NULL,
  `msg_to` int(11) NOT NULL,
  `message` text NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  `status` enum('read','unread') NOT NULL DEFAULT 'unread',
  FOREIGN KEY(`msg_by`) REFERENCES users(`id`) ON DELETE CASCADE,
  FOREIGN KEY(`msg_to`) REFERENCES users(`id`) ON DELETE CASCADE
);

CREATE TABLE `notifications` (
`noti_id` int(11) NOT NULL AUTO_INCREMENT,
`notify_by` int(11) NOT NULL,
`notify_to` int(11) NOT NULL,
`time` datetime NOT NULL DEFAULT NOW(),
`type` enum('comment', 'follow', 'like', 'message', 'mention') NOT NULL,
FOREIGN KEY(`notify_by`) REFERENCES users(`id`) ON DELETE CASCADE,
FOREIGN KEY(`notify_to`) REFERENCES users(`id`) ON DELETE CASCADE,
PRIMARY KEY(`noti_id`, `notify_by`, `notify_to`)
);

CREATE TABLE `notify_of_follow` (
  `noti_id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `follow_id` int(11) NOT NULL,
  `notify_by` int(11) NOT NULL,
  `notify_to` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  `status` enum('read','unread') NOT NULL DEFAULT 'unread',
  FOREIGN KEY(`noti_id`) REFERENCES notifications(`noti_id`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_by`) REFERENCES notifications(`notify_by`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_to`) REFERENCES notifications(`notify_to`) ON DELETE CASCADE,
  FOREIGN KEY(`follow_id`) REFERENCES follow_system(`follow_id`) ON DELETE CASCADE
);

CREATE TABLE `notify_of_like` (
  `noti_id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `like_id` int(11) NOT NULL,
  `notify_by` int(11) NOT NULL,
  `notify_to` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  `status` enum('read','unread') NOT NULL DEFAULT 'unread',
  FOREIGN KEY(`like_id`) REFERENCES likes(`like_id`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_by`) REFERENCES notifications(`notify_by`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_to`) REFERENCES notifications(`notify_to`) ON DELETE CASCADE
);

CREATE TABLE `notify_of_comment` (
  `noti_id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `comment` int(11) NOT NULL,
  `notify_by` int(11) NOT NULL,
  `notify_to` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  `status` enum('read','unread') NOT NULL DEFAULT 'unread',
  FOREIGN KEY(`comment`) REFERENCES comments(`comment_id`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_by`) REFERENCES notifications(`notify_by`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_to`) REFERENCES notifications(`notify_to`) ON DELETE CASCADE
);

CREATE TABLE `notify_of_message` (
  `noti_id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `message_id` int(11) NOT NULL,
  `notify_by` int(11) NOT NULL,
  `notify_to` int(11) NOT NULL,
  `time` datetime NOT NULL DEFAULT NOW(),
  `status` enum('read','unread') NOT NULL DEFAULT 'unread',
  FOREIGN KEY(`message_id`) REFERENCES message(`message_id`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_by`) REFERENCES notifications(`notify_by`) ON DELETE CASCADE,
  FOREIGN KEY(`notify_to`) REFERENCES notifications(`notify_to`) ON DELETE CASCADE
);

CREATE TABLE `block` (
  `block_id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `block_by` int(11) NOT NULL,
  `block_to` int(11) NOT NULL,
  FOREIGN KEY(`block_by`) REFERENCES users(`id`) ON DELETE CASCADE,
  FOREIGN KEY(`block_to`) REFERENCES users(`id`) ON DELETE CASCADE
);