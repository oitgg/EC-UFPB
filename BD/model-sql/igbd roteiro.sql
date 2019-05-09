#1 Adicionar usuários
INSERT INTO `users` (`id`, `username`, `firstname`, `surname`, `password`, `bio`, `type`) VALUES
(null, 'alex', 'alex', 'silva', 'senhaalex', 'moro em jp', 'public'),
(null, 'bruninha', 'bruna', 'brasil', 'senhabruna', 'moro em cg', 'public'),
(null, 'caio', 'caio', 'silva', 'senhacaio', 'moro em jp', 'private'),
(null, 'vovo', 'dalila', 'dias', 'senhadalila', 'moro em natal', 'private');

====================================================================================================

#2 Como ALEX
SELECT * FROM users WHERE `username` = 'alex' AND `password` = 'senhaalex'

#3 Postar `bom dia #bd`
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 1, 'http://img.com/1.png', 'bom dia #bd', DEFAULT)

#3.1 Inserir #bd nas hashtags
INSERT INTO `hashtag` (`hashtag_id`, `hashtag_name`, `src_post`, `user_id`, `time`, `type_src`) VALUES
(null, 'bd', 1, 1, DEFAULT, 'post')

#4 Postar `boa tarde`
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 1, 'http://img.com/2.png', 'boa tarde', DEFAULT)

#5 Postar `boa noite`
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 1, 'http://img.com/3.png', 'boa noite', DEFAULT)

#6 Seguir Bruna
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 1, 2, DEFAULT, DEFAULT)

#6.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 1, 2, DEFAULT, 'follow')

#6.2 Notificar Bruna
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 1, 1, 2, DEFAULT, DEFAULT)

#7 Seguir Caio
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 1, 3, DEFAULT, 'pending')

#7.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 1, 3, DEFAULT, 'follow')

#7.2 Notificar Caio
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 2, 1, 3, DEFAULT, DEFAULT)

#8 Seguir Dalila
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 1, 4, DEFAULT, 'pending')

#8.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 1, 4, DEFAULT, 'follow')

#8.2 Notificar Dalila
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 3, 1, 4, DEFAULT, DEFAULT)


====================================================================================================

#9 Como BRUNA
SELECT * FROM users WHERE `username` = 'bruninha' AND `password` = 'senhabruna'

#10 Acesse as notificações de BRUNA
SELECT * FROM notifications WHERE `notify_to` = '2';
UPDATE notify_of_follow SET status = 'read' WHERE notify_to = '2';
UPDATE notify_of_like SET status = 'read' WHERE notify_to = '2';
UPDATE notify_of_comment SET status = 'read' WHERE notify_to = '2';
UPDATE notify_of_message SET status = 'read' WHERE notify_to = '2';

#11 Acesse o perfil do seu novo seguidor
SELECT username, firstname, surname, bio FROM users WHERE username = 'alex'

#12 Siga Alex
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 2, 1, DEFAULT, DEFAULT)

#12.1 Notification Index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 2, 1, DEFAULT, 'follow')

#12.2 Notificar Alex
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 4, 2, 1, DEFAULT, DEFAULT)

#12 Acesse as postagens de Alex
SELECT u.username, p.post_id, p.image_url, p.description, p.time FROM users u JOIN post p ON (p.user_id = u.id) WHERE username = 'alex'
#SELECT COUNT (DISTINCT followee_id) FROM follow_system WHERE follower_id = '1'

#13 Acesse os comentários da postagem 'bom dia #bd'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '1'

#13.2 Comentar 'oi alex'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'oi alex', 1, 2, DEFAULT)

#13.3 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 2, 1, DEFAULT, 'comment')

#13.4 Notificar Alex
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 1, 2, 1, DEFAULT, DEFAULT)

#14 Siga Caio
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 2, 3, DEFAULT, 'pending')

#14.1 Index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 2, 3, DEFAULT, 'follow')

#14.2 Notificar Caio
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 5, 2, 3, DEFAULT, DEFAULT)

#15 Siga Dalila
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 2, 4, DEFAULT, 'pending')

#15.1 Index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 2, 4, DEFAULT, 'follow')

#15.2 Notificar Dalila
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 6, 2, 4, DEFAULT, DEFAULT)

#16 Publique 'ola, gente'
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 2, 'http://img.com/4.png', 'ola, gente', DEFAULT)

====================================================================================================

#17 Como Caio
SELECT * FROM users WHERE `username` = 'caio' AND `password` = 'senhacaio'

#18 Acesse as notificações
SELECT * FROM notifications WHERE `notify_to` = '3'
UPDATE notify_of_follow SET status = 'read' WHERE notify_to = '3'

#19 Aceite a solicitação de Alex
UPDATE follow_system SET status = 'accepted' WHERE follow_id = '2'

#20 Siga Alex
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 3, 1, DEFAULT, DEFAULT)

#20.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 3, 1, DEFAULT, 'follow')

#20.2 Notificar Alex
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 7, 3, 1, DEFAULT, DEFAULT)

#21 Acesse os comentários da postagem 'bom dia #bd'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '1'

#21.1 Comente 'oi @bruninha'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'oi @bruninha', 1, 3, DEFAULT)

#21.2 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 3, 1, DEFAULT, 'comment')
(null, 3, 2, DEFAULT, 'mention')

#21.3 Notificar Alex (Comentário)
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 2, 3, 1, DEFAULT, DEFAULT)

#21.4 Notificar Bruna (Menção)
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 2, 3, 2, DEFAULT, DEFAULT)

#22 Aceitar a solicitação de Bruna
UPDATE follow_system SET status = 'accepted' WHERE follow_id = '5'

#23 Seguir Bruna
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 3, 2, DEFAULT, DEFAULT)

#23.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 3, 2, DEFAULT, 'follow')

#23.2 Notificar Bruna
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 8, 3, 2, DEFAULT, DEFAULT)

#24 Acesse os comentários da postagem 'ola, gente'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '4';

#24.2 Comente 'oi, bb'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'oi, bb', 4, 3, DEFAULT)

#24.2 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 3, 2, DEFAULT, 'comment')

#24.3 Notificar Bruna (comentário)
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 3, 3, 2, DEFAULT, DEFAULT)

#25 Siga Dalila
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 3, 4, DEFAULT, 'pending')

#25.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 3, 4, DEFAULT, 'follow')

#25.2 Notificar Dalila
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 9, 3, 4, DEFAULT, DEFAULT)

#26 Publicar 'quanta gente, quanta alegria'
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 3, 'http://img.com/5.png', 'quanta gente, quanta alegria?', DEFAULT)

====================================================================================================

#26 Como Dalila
SELECT * FROM users WHERE `username` = 'vovo' AND `password` = 'senhadalila'

#27 Acesse as notificações
SELECT * FROM notifications WHERE `notify_to` = '4';
UPDATE notify_of_follow SET status = 'read' WHERE notify_to = '4';

#28 Siga Bruna
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 4, 2, DEFAULT, DEFAULT)

#28.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 4, 2, DEFAULT, 'follow')

#28.2 Notificar Bruna
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 10, 3, 4, DEFAULT, DEFAULT)

#29 Seguir Caio
INSERT INTO `follow_system` (`follow_id`, `follower_id`, `followee_id`, `time`, `status`) VALUES
(null, 4, 3, DEFAULT, 'pending')

#29.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 4, 3, DEFAULT, 'follow')

#29.2 Notificar Caio
INSERT INTO `notify_of_follow` (`noti_id`, `follow_id`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 11, 3, 4, DEFAULT, DEFAULT)

====================================================================================================

#30 Como Bruna
SELECT * FROM users WHERE `username` = 'bruninha' AND `password` = 'senhabruna'

#31 Acesse as notificações
SELECT * FROM notifications WHERE `notify_to` = '2';
UPDATE notify_of_follow SET status = 'read' WHERE notify_to = '2';
UPDATE notify_of_comment SET status = 'read' WHERE notify_to = '2';

#32 Acesse a postagem que você foi marcada
SELECT post_id, user_id, content FROM comments WHERE content LIKE '%@bruninha%' 

#33 Acesse as notificações
SELECT * FROM notifications WHERE `notify_to` = '2';

#34 Publique 'qual é a boa?'
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 2, 'http://img.com/6.png', 'qual é a boa?', DEFAULT)

#35 Acesse os comentários da postagem 'quanta gente, quanta alegria'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '5';

#35 Comente 'a minha felicidade'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'a minha felicidade', 5, 2, DEFAULT)

#35.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 2, 3, DEFAULT, 'comment')

#35.2 Notificar Caio
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 4, 2, 3, DEFAULT, DEFAULT)

====================================================================================================

#36 Como Caio
SELECT * FROM users WHERE `username` = 'caio' AND `password` = 'senhacaio'

#37 Acessar as notificações
SELECT * FROM notifications WHERE `notify_to` = '3';
UPDATE notify_of_follow SET status = 'read' WHERE notify_to = '3';
UPDATE notify_of_comment SET status = 'read' WHERE notify_to = '3';

#38 Aceite a solicitação de Dalila
UPDATE follow_system SET status = 'accepted' WHERE follow_id = '11';

#39 Acesse a linha do tempo (de quem?)
SELECT u.username, p.post_id, p.image_url, p.description, p.time FROM users u JOIN post p ON (p.user_id = u.id) WHERE username = 'caio';
SELECT u.username, p.post_id, p.image_url, p.description, p.time FROM users u JOIN post p ON (p.user_id = u.id) WHERE username = 'vovo';

#40 Acesse os comentários da postagem 'bom dia #bd'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '1';

#41 Comente 'fala @alex'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'fala @alex', 3, 1, DEFAULT);

#42.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 3, 1, DEFAULT, 'comment'),
(null, 3, 1, DEFAULT, 'mention');

#42.2 Notificar Alex (Comentário)
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 5, 3, 1, DEFAULT, DEFAULT);

#42.3 Notificar Alex (Menção)
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 5, 3, 1, DEFAULT, DEFAULT);

====================================================================================================

#43 Como Alex
SELECT * FROM users WHERE `username` = 'alex' AND `password` = 'senhaalex'

#44 Acesse os comentários da postagem 'quanta gente, quanta alegria'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '5';

#45 Comente 'eh a aula de #bd'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'eh a aula de #bd', 5, 1, DEFAULT);

#45.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 1, 3, DEFAULT, 'comment');

#45.2 Notificar Caio
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 6, 1, 3, DEFAULT, DEFAULT);

#46 Inserir #bd nas hashtags
INSERT INTO `hashtag` (`hashtag_id`, `hashtag_name`, `src_post`, `user_id`, `time`, `type_src`) VALUES
(null, 'bd', 5, 1, DEFAULT, 'comment')

====================================================================================================

#47 Como Caio
SELECT * FROM users WHERE `username` = 'caio' AND `password` = 'senhacaio';

#48 Acesse os comentários da postagem 'quanta gente, quanta alegria'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '5';

#49 Comente 'perfeito!'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'perfeito!', 5, 3, DEFAULT);

#50 Publique 'paródia de mamonas assassinas'
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 3, 'http://img.com/76.png', 'paródia de mamonas assassinas', DEFAULT);

====================================================================================================

#51 Como Alex
SELECT * FROM users WHERE `username` = 'alex' AND `password` = 'senhaalex'

#52 Acesse as notificações
SELECT * FROM notifications WHERE `notify_to` = '1';
UPDATE notify_of_follow SET status = 'read' WHERE notify_to = '1';
UPDATE notify_of_comment SET status = 'read' WHERE notify_to = '1';

#53 Acesse os comentários da postagem 'bom dia #bd'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '1';

#54 Comente 'simbora!'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'simbora!', 1, 1, DEFAULT);

#55 Acesse os comentários da postagem 'ola, gente'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '4';

#56 Comente 'cheguei...'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'cheguei...', 4, 1, DEFAULT);

#56.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 1, 2, DEFAULT, 'comment');

#57.1 Notificar Bruna
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 9, 1, 2, DEFAULT, DEFAULT);

#58 Acesse os comentários da postagem 'qual é a boa?'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '6';

#59 Comente 'vamos jogar bola?'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'vamos jogar bola?', 6, 1, DEFAULT);

#59.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 1, 2, DEFAULT, 'comment');

#59.2 Notificar Bruna
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 10, 1, 2, DEFAULT, DEFAULT);

====================================================================================================

#60 Como Dalila
SELECT * FROM users WHERE `username` = 'vovo' AND `password` = 'senhadalila';

#61 Publique 'o meu neto @caio eh lindo'
INSERT INTO `post` (`post_id`, `user_id`, `image_url`, `description`, `time`) VALUES
(null, 4, 'http://img.com/8.png', 'o meu neto @caio eh lindo', DEFAULT);

#61.2 Marcar Caio na publicação 
INSERT INTO `photo_tag` (`photo_id`, `who_tag`) VALUES
(8, 'caio');

#61.3 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 4, 3, DEFAULT, 'mention');

#62 Acessar os comentários da postagem 'qual é a boa?'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '6';

#63 Comentar 'vao estudar!'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'vao estudar!', 6, 4, DEFAULT);

#63.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 4, 2, DEFAULT, 'comment');

#63.2 Notificar Bruna
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 11, 4, 2, DEFAULT, DEFAULT);

#64 Acessar os comentários da postagem 'parodia de mamonas assassinas'
SELECT p.post_id, p.user_id, p.image_url, p.description, p.time, c.comment_id, c.user_id, c.content, c.time FROM post p JOIN comments c ON (p.post_id = c.post_id) WHERE c.post_id = '7';

#65 Comentar 'vai estudar #bd'
INSERT INTO `comments` (`comment_id`, `content`, `post_id`, `user_id`, `time`) VALUES  
(null, 'vai estudar #bd', 7, 4, DEFAULT);

#65.1 Notification index
INSERT INTO `notifications` (`noti_id`, `notify_by`, `notify_to`, `time`, `type`) VALUES
(null, 4, 3, DEFAULT, 'comment');

#65.2 Notificar Caio
INSERT INTO `notify_of_comment` (`noti_id`, `comment`, `notify_by`, `notify_to`, `time`, `status`) VALUES
(null, 12, 4, 3, DEFAULT, DEFAULT);

#66 Inserir #bd nas hashtags
INSERT INTO `hashtag` (`hashtag_id`, `hashtag_name`, `src_post`, `user_id`, `time`, `type_src`) VALUES
(null, 'bd', 5, 1, DEFAULT, 'comment');

#67 Busque por '#bd'
SELECT * FROM hashtag WHERE hashtag_name = 'bd';

#68 Busque por 'silva'
SELECT username, firstname, surname FROM users WHERE surname LIKE '%silva%';
SELECT username, firstname, surname FROM users WHERE username LIKE '%silva%';
SELECT content FROM comments WHERE content LIKE '%silva%';
SELECT hashtag_name, src_post FROM hashtag WHERE hashtag_name LIKE '%silva%';  

====================================================================================================

#69 Como Caio
SELECT * FROM users WHERE `username` = 'caio' AND `password` = 'senhacaio';

#70 Acesse as notificações
SELECT * FROM notifications WHERE `notify_to` = '3';
UPDATE notify_of_follow SET status = 'read' WHERE notify_to = '3';
UPDATE notify_of_comment SET status = 'read' WHERE notify_to = '3';

#71 Busque por 'silva'
SELECT username, firstname, surname FROM users WHERE surname LIKE '%vovo%';
SELECT username, firstname, surname FROM users WHERE username LIKE '%vovo%';
SELECT content FROM comments WHERE content LIKE '%vovo%';
SELECT hashtag_name, src_post FROM hashtag WHERE hashtag_name LIKE '%vovo%';  

====================================================================================================

#72 Como Alex
SELECT * FROM users WHERE `username` = 'alex' AND `password` = 'senhaalex';

#73 Apague o comentário 'oi @bruninha' na postagem 'bom dia #bd'
DELETE FROM comments WHERE comment_id = '2';

#74 Apague a postagem 'boa noite'
DELETE FROM post WHERE post_id = '3';

#75 Apague a postagem 'boa tarde'
DELETE FROM post WHERE post_id = '2';

====================================================================================================

#76 Como Bruna
SELECT * FROM users WHERE `username` = 'bruninha' AND `password` = 'senhabruna'

#77 Bloquear Alex
INSERT INTO `block` (`block_id`, `block_by`, `block_to`) VALUES (null, 2, 1);
DELETE FROM follow_system WHERE follow_id = '4';