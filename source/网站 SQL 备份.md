CREATE TABLE `users` (

  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,

  `name` varchar(191) DEFAULT NULL,

  `password_digest` varchar(255) DEFAULT NULL,

  `status` varchar(255) DEFAULT NULL,

  `yuan_key` varchar(255) DEFAULT NULL,

  `max_folder` int(11) DEFAULT '8',

  `max_link` int(11) DEFAULT '120',

  `rm_ad` tinyint(1) DEFAULT '0',

  `level` int(11) DEFAULT '1',

  `created_at` datetime(3) DEFAULT NULL,

  `js_token` varchar(255) DEFAULT NULL,

  `vip_time` datetime(3) DEFAULT NULL,

  PRIMARY KEY (`id`),

  UNIQUE KEY `idx_name` (`name`) USING HASH COMMENT '不分组不排序不重复的名称'

) ENGINE=InnoDB AUTO_INCREMENT=19054 DEFAULT CHARSET=utf8mb4

CREATE TABLE `sites` (

  `music` varchar(2001) DEFAULT '',

  `top_bottom` varchar(2000) DEFAULT '',

  PRIMARY KEY (`id`),

  UNIQUE KEY `idx_site_uid` (`user_id`) USING HASH

) ENGINE=InnoDB AUTO_INCREMENT=19054 DEFAULT CHARSET=utf8mb4

ALTER TABLE users 

ADD COLUMN site_basic JSON,

ADD COLUMN site_music JSON,

ADD COLUMN site_top_bottom JSON;

UPDATE users AS B

SET B.site_basic = (SELECT JSON_OBJECT('name', name, 'info', info, 'bg', bg, 'color' ,color,'bg_lizi' ,bg_lizi,'bg_switch' ,bg_switch,'bg_color' ,bg_color,'font_color' ,font_color,'mobile_bg' ,mobile_bg) AS site_basic FROM sites AS A WHERE A.user_id = B.id);

UPDATE users AS B

SET B.site_music = (SELECT music FROM sites AS A where A.user_id = B.id and A.music <> '');

UPDATE users AS B

SET B.site_top_bottom = (SELECT top_bottom FROM sites AS A where A.user_id = B.id and A.top_bottom <> '');

ALTER Table users

Add COLUMN subscribe JSON;

\# 清理一年前的不活跃账号

SELECT * from users where id in (select user_id from links GROUP BY user_id HAVING  count(1) <= 2) and (created_at < '2022-08-31' or created_at is null);