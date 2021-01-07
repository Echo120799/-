/*
 Navicat Premium Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 50723
 Source Host           : localhost
 Source Database       : trade

 Target Server Type    : MySQL
 Target Server Version : 50723
 File Encoding         : utf-8

 Date: 06/25/2020 18:30:40 PM
*/

SET NAMES utf8;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
--  Table structure for `auth_group`
-- ----------------------------
DROP TABLE IF EXISTS `auth_group`;
CREATE TABLE `auth_group` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(80) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Table structure for `auth_group_permissions`
-- ----------------------------
DROP TABLE IF EXISTS `auth_group_permissions`;
CREATE TABLE `auth_group_permissions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `group_id` int(11) NOT NULL,
  `permission_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_group_permissions_group_id_permission_id_0cd325b0_uniq` (`group_id`,`permission_id`),
  KEY `auth_group_permissio_permission_id_84c5c92e_fk_auth_perm` (`permission_id`),
  CONSTRAINT `auth_group_permissio_permission_id_84c5c92e_fk_auth_perm` FOREIGN KEY (`permission_id`) REFERENCES `auth_permission` (`id`),
  CONSTRAINT `auth_group_permissions_group_id_b120cbf9_fk_auth_group_id` FOREIGN KEY (`group_id`) REFERENCES `auth_group` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Table structure for `auth_permission`
-- ----------------------------
DROP TABLE IF EXISTS `auth_permission`;
CREATE TABLE `auth_permission` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) COLLATE utf8_bin NOT NULL,
  `content_type_id` int(11) NOT NULL,
  `codename` varchar(100) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_permission_content_type_id_codename_01ab375a_uniq` (`content_type_id`,`codename`),
  CONSTRAINT `auth_permission_content_type_id_2f476e4b_fk_django_co` FOREIGN KEY (`content_type_id`) REFERENCES `django_content_type` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `auth_permission`
-- ----------------------------
BEGIN;
INSERT INTO `auth_permission` VALUES ('1', 'Can add log entry', '1', 'add_logentry'), ('2', 'Can change log entry', '1', 'change_logentry'), ('3', 'Can delete log entry', '1', 'delete_logentry'), ('4', 'Can add permission', '2', 'add_permission'), ('5', 'Can change permission', '2', 'change_permission'), ('6', 'Can delete permission', '2', 'delete_permission'), ('7', 'Can add group', '3', 'add_group'), ('8', 'Can change group', '3', 'change_group'), ('9', 'Can delete group', '3', 'delete_group'), ('10', 'Can add content type', '4', 'add_contenttype'), ('11', 'Can change content type', '4', 'change_contenttype'), ('12', 'Can delete content type', '4', 'delete_contenttype'), ('13', 'Can add session', '5', 'add_session'), ('14', 'Can change session', '5', 'change_session'), ('15', 'Can delete session', '5', 'delete_session'), ('16', 'Can add 评论', '6', 'add_commentdetailmodel'), ('17', 'Can change 评论', '6', 'change_commentdetailmodel'), ('18', 'Can delete 评论', '6', 'delete_commentdetailmodel'), ('19', 'Can add 留言', '7', 'add_commentmodel'), ('20', 'Can change 留言', '7', 'change_commentmodel'), ('21', 'Can delete 留言', '7', 'delete_commentmodel'), ('22', 'Can add 物品', '8', 'add_item'), ('23', 'Can change 物品', '8', 'change_item'), ('24', 'Can delete 物品', '8', 'delete_item'), ('25', 'Can add 购买记录', '9', 'add_ordermodel'), ('26', 'Can change 购买记录', '9', 'change_ordermodel'), ('27', 'Can delete 购买记录', '9', 'delete_ordermodel'), ('28', 'Can add 用户信息', '10', 'add_userprofile'), ('29', 'Can change 用户信息', '10', 'change_userprofile'), ('30', 'Can delete 用户信息', '10', 'delete_userprofile');
COMMIT;

-- ----------------------------
--  Table structure for `custom_user_userprofile`
-- ----------------------------
DROP TABLE IF EXISTS `custom_user_userprofile`;
CREATE TABLE `custom_user_userprofile` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `password` varchar(128) COLLATE utf8_bin NOT NULL,
  `last_login` datetime(6) DEFAULT NULL,
  `is_superuser` tinyint(1) NOT NULL,
  `username` varchar(150) COLLATE utf8_bin NOT NULL,
  `first_name` varchar(30) COLLATE utf8_bin NOT NULL,
  `last_name` varchar(30) COLLATE utf8_bin NOT NULL,
  `email` varchar(254) COLLATE utf8_bin NOT NULL,
  `is_staff` tinyint(1) NOT NULL,
  `is_active` tinyint(1) NOT NULL,
  `date_joined` datetime(6) NOT NULL,
  `sex` int(11) NOT NULL,
  `mobile` varchar(11) COLLATE utf8_bin DEFAULT NULL,
  `image` varchar(100) COLLATE utf8_bin NOT NULL,
  `address` varchar(100) COLLATE utf8_bin NOT NULL,
  `interest` varchar(255) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `custom_user_userprofile`
-- ----------------------------
BEGIN;
INSERT INTO `custom_user_userprofile` VALUES ('1', 'pbkdf2_sha256$36000$D4pva1L3owPZ$smp6DCX/dSenZqFLrEB7vQewXV8c1AjlMesTb7WbHmA=', '2020-06-25 18:21:01.877631', '1', 'admin', '', '', 'dsg@qq.com', '1', '1', '2020-06-25 18:18:12.347871', '0', null, 'img/default.jpg', '', null);
COMMIT;

-- ----------------------------
--  Table structure for `custom_user_userprofile_groups`
-- ----------------------------
DROP TABLE IF EXISTS `custom_user_userprofile_groups`;
CREATE TABLE `custom_user_userprofile_groups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userprofile_id` int(11) NOT NULL,
  `group_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `custom_user_userprofile__userprofile_id_group_id_1e7cac9e_uniq` (`userprofile_id`,`group_id`),
  KEY `custom_user_userprof_group_id_c64c4830_fk_auth_grou` (`group_id`),
  CONSTRAINT `custom_user_userprof_group_id_c64c4830_fk_auth_grou` FOREIGN KEY (`group_id`) REFERENCES `auth_group` (`id`),
  CONSTRAINT `custom_user_userprof_userprofile_id_85b5ca69_fk_custom_us` FOREIGN KEY (`userprofile_id`) REFERENCES `custom_user_userprofile` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Table structure for `custom_user_userprofile_user_permissions`
-- ----------------------------
DROP TABLE IF EXISTS `custom_user_userprofile_user_permissions`;
CREATE TABLE `custom_user_userprofile_user_permissions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userprofile_id` int(11) NOT NULL,
  `permission_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `custom_user_userprofile__userprofile_id_permissio_59bf8298_uniq` (`userprofile_id`,`permission_id`),
  KEY `custom_user_userprof_permission_id_ecb03db0_fk_auth_perm` (`permission_id`),
  CONSTRAINT `custom_user_userprof_permission_id_ecb03db0_fk_auth_perm` FOREIGN KEY (`permission_id`) REFERENCES `auth_permission` (`id`),
  CONSTRAINT `custom_user_userprof_userprofile_id_954fc757_fk_custom_us` FOREIGN KEY (`userprofile_id`) REFERENCES `custom_user_userprofile` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Table structure for `django_admin_log`
-- ----------------------------
DROP TABLE IF EXISTS `django_admin_log`;
CREATE TABLE `django_admin_log` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `action_time` datetime(6) NOT NULL,
  `object_id` longtext COLLATE utf8_bin,
  `object_repr` varchar(200) COLLATE utf8_bin NOT NULL,
  `action_flag` smallint(5) unsigned NOT NULL,
  `change_message` longtext COLLATE utf8_bin NOT NULL,
  `content_type_id` int(11) DEFAULT NULL,
  `user_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `django_admin_log_content_type_id_c4bce8eb_fk_django_co` (`content_type_id`),
  KEY `django_admin_log_user_id_c564eba6_fk_custom_user_userprofile_id` (`user_id`),
  CONSTRAINT `django_admin_log_content_type_id_c4bce8eb_fk_django_co` FOREIGN KEY (`content_type_id`) REFERENCES `django_content_type` (`id`),
  CONSTRAINT `django_admin_log_user_id_c564eba6_fk_custom_user_userprofile_id` FOREIGN KEY (`user_id`) REFERENCES `custom_user_userprofile` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `django_admin_log`
-- ----------------------------
BEGIN;
INSERT INTO `django_admin_log` VALUES ('1', '2020-06-25 18:24:30.078647', 0x31, '小米电视机', '1', 0x5b7b226164646564223a207b7d7d5d, '8', '1');
COMMIT;

-- ----------------------------
--  Table structure for `django_content_type`
-- ----------------------------
DROP TABLE IF EXISTS `django_content_type`;
CREATE TABLE `django_content_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `app_label` varchar(100) COLLATE utf8_bin NOT NULL,
  `model` varchar(100) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `django_content_type_app_label_model_76bd3d3b_uniq` (`app_label`,`model`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `django_content_type`
-- ----------------------------
BEGIN;
INSERT INTO `django_content_type` VALUES ('1', 'admin', 'logentry'), ('3', 'auth', 'group'), ('2', 'auth', 'permission'), ('4', 'contenttypes', 'contenttype'), ('10', 'custom_user', 'userprofile'), ('6', 'market', 'commentdetailmodel'), ('7', 'market', 'commentmodel'), ('8', 'market', 'item'), ('9', 'market', 'ordermodel'), ('5', 'sessions', 'session');
COMMIT;

-- ----------------------------
--  Table structure for `django_migrations`
-- ----------------------------
DROP TABLE IF EXISTS `django_migrations`;
CREATE TABLE `django_migrations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `app` varchar(255) COLLATE utf8_bin NOT NULL,
  `name` varchar(255) COLLATE utf8_bin NOT NULL,
  `applied` datetime(6) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `django_migrations`
-- ----------------------------
BEGIN;
INSERT INTO `django_migrations` VALUES ('1', 'contenttypes', '0001_initial', '2020-06-25 18:14:01.965344'), ('2', 'contenttypes', '0002_remove_content_type_name', '2020-06-25 18:14:02.002085'), ('3', 'auth', '0001_initial', '2020-06-25 18:14:02.154366'), ('4', 'auth', '0002_alter_permission_name_max_length', '2020-06-25 18:14:02.171697'), ('5', 'auth', '0003_alter_user_email_max_length', '2020-06-25 18:14:02.181012'), ('6', 'auth', '0004_alter_user_username_opts', '2020-06-25 18:14:02.192632'), ('7', 'auth', '0005_alter_user_last_login_null', '2020-06-25 18:14:02.200788'), ('8', 'auth', '0006_require_contenttypes_0002', '2020-06-25 18:14:02.203057'), ('9', 'auth', '0007_alter_validators_add_error_messages', '2020-06-25 18:14:02.209748'), ('10', 'auth', '0008_alter_user_username_max_length', '2020-06-25 18:14:02.226578'), ('11', 'custom_user', '0001_initial', '2020-06-25 18:14:02.384242'), ('12', 'admin', '0001_initial', '2020-06-25 18:14:02.460949'), ('13', 'admin', '0002_logentry_remove_auto_add', '2020-06-25 18:14:02.488978'), ('14', 'market', '0001_initial', '2020-06-25 18:14:02.679107'), ('15', 'sessions', '0001_initial', '2020-06-25 18:14:02.715563');
COMMIT;

-- ----------------------------
--  Table structure for `django_session`
-- ----------------------------
DROP TABLE IF EXISTS `django_session`;
CREATE TABLE `django_session` (
  `session_key` varchar(40) COLLATE utf8_bin NOT NULL,
  `session_data` longtext COLLATE utf8_bin NOT NULL,
  `expire_date` datetime(6) NOT NULL,
  PRIMARY KEY (`session_key`),
  KEY `django_session_expire_date_a5c62663` (`expire_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `django_session`
-- ----------------------------
BEGIN;
INSERT INTO `django_session` VALUES ('ff6rm7kxmkbxz1vjay2k67b0sbewbyl6', 0x4e7a5a6c4d6a673259324668596d4a6b4e574a6d597a46694e7a55304f57466b4f47466c4e324532596d5a6b5a544977597a6b774d447037496c39686458526f5833567a5a584a66615751694f69497849697769583246316447686664584e6c636c396959574e725a57356b496a6f695933567a644739745833567a5a584975646d6c6c64334d755133567a64473974516d466a613256755a434973496c39686458526f5833567a5a584a666147467a61434936496a59315954566a4e6d4d795a44637a5a57526a4e5751314d7a67324f444535597a67304d7a426959574933597a51345a44426c4f57496966513d3d, '2020-07-09 18:21:01.884179');
COMMIT;

-- ----------------------------
--  Table structure for `market_commentdetailmodel`
-- ----------------------------
DROP TABLE IF EXISTS `market_commentdetailmodel`;
CREATE TABLE `market_commentdetailmodel` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pic` varchar(100) COLLATE utf8_bin NOT NULL,
  `description` longtext COLLATE utf8_bin NOT NULL,
  `create_at` datetime(6) NOT NULL,
  `order_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `market_commentdetailmodel_order_id_7a2b3a65_fk_market_order_id` (`order_id`),
  KEY `market_commentdetail_user_id_a36e685b_fk_custom_us` (`user_id`),
  CONSTRAINT `market_commentdetail_user_id_a36e685b_fk_custom_us` FOREIGN KEY (`user_id`) REFERENCES `custom_user_userprofile` (`id`),
  CONSTRAINT `market_commentdetailmodel_order_id_7a2b3a65_fk_market_order_id` FOREIGN KEY (`order_id`) REFERENCES `market_order` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Table structure for `market_commentmodel`
-- ----------------------------
DROP TABLE IF EXISTS `market_commentmodel`;
CREATE TABLE `market_commentmodel` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user` varchar(256) COLLATE utf8_bin NOT NULL,
  `description` longtext COLLATE utf8_bin NOT NULL,
  `create_at` datetime(6) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Table structure for `market_item`
-- ----------------------------
DROP TABLE IF EXISTS `market_item`;
CREATE TABLE `market_item` (
  `create_at` datetime(6) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `classification` int(11) NOT NULL,
  `name` varchar(256) COLLATE utf8_bin NOT NULL,
  `description` longtext COLLATE utf8_bin,
  `has_sale` int(11) NOT NULL,
  `pic` varchar(100) COLLATE utf8_bin NOT NULL,
  `price` double NOT NULL,
  `counts` int(11) NOT NULL,
  `phone` varchar(11) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `market_item`
-- ----------------------------
BEGIN;
INSERT INTO `market_item` VALUES ('2020-06-25 18:24:30.071338', '1', '1', '小米电视机', 0xe998bfe7919fe8b4b9e4b8aae5a4a7e698afe5a4a7e99d9ee59b9ee5a48de794b5e8af9d, '1', 'img/dianshi.jpg', '1000', '11', '11111111111');
COMMIT;

-- ----------------------------
--  Table structure for `market_order`
-- ----------------------------
DROP TABLE IF EXISTS `market_order`;
CREATE TABLE `market_order` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `order_id` varchar(128) COLLATE utf8_bin NOT NULL,
  `status` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `price` double NOT NULL,
  `address` varchar(256) COLLATE utf8_bin NOT NULL,
  `phone` varchar(11) COLLATE utf8_bin NOT NULL,
  `create_at` datetime(6) NOT NULL,
  `good_item_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `order_id` (`order_id`),
  KEY `market_order_good_item_id_f2e3a749_fk_market_item_id` (`good_item_id`),
  KEY `market_order_user_id_9282bbe2_fk_custom_user_userprofile_id` (`user_id`),
  CONSTRAINT `market_order_good_item_id_f2e3a749_fk_market_item_id` FOREIGN KEY (`good_item_id`) REFERENCES `market_item` (`id`),
  CONSTRAINT `market_order_user_id_9282bbe2_fk_custom_user_userprofile_id` FOREIGN KEY (`user_id`) REFERENCES `custom_user_userprofile` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
--  Records of `market_order`
-- ----------------------------
BEGIN;
INSERT INTO `market_order` VALUES ('1', '1dc5f362-b6ce-11ea-b079-f218982593a3', '1', '1', '1000', '请选择省请选择市请选择区而复古', '11111111112', '2020-06-25 18:24:56.763503', '1', '1');
COMMIT;

SET FOREIGN_KEY_CHECKS = 1;
