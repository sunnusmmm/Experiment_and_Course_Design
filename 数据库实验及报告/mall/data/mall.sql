/*
 Navicat Premium Data Transfer

 Source Server         : First
 Source Server Type    : MySQL
 Source Server Version : 80016
 Source Host           : localhost:3306
 Source Schema         : mall

 Target Server Type    : MySQL
 Target Server Version : 80016
 File Encoding         : 65001

 Date: 30/06/2020 08:34:33
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for admin_user
-- ----------------------------
DROP TABLE IF EXISTS `admin_user`;
CREATE TABLE `admin_user`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `username` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of admin_user
-- ----------------------------
INSERT INTO `admin_user` VALUES (1, 'admin', 'admin');

-- ----------------------------
-- Table structure for classification
-- ----------------------------
DROP TABLE IF EXISTS `classification`;
CREATE TABLE `classification`  (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID',
  `cname` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '类别名',
  `type` int(11) NULL DEFAULT NULL COMMENT '标记',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 19 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of classification
-- ----------------------------
INSERT INTO `classification` VALUES (2, '电脑', 1);
INSERT INTO `classification` VALUES (4, '食品', 1);
INSERT INTO `classification` VALUES (6, '图书', 1);
INSERT INTO `classification` VALUES (7, '鞋子', 1);
INSERT INTO `classification` VALUES (11, '智能手机', 1);
INSERT INTO `classification` VALUES (13, '手表', 1);
INSERT INTO `classification` VALUES (17, '衣服', 1);
INSERT INTO `classification` VALUES (18, '家具', 1);

-- ----------------------------
-- Table structure for order
-- ----------------------------
DROP TABLE IF EXISTS `order`;
CREATE TABLE `order`  (
  `id` int(10) NOT NULL AUTO_INCREMENT COMMENT 'ID',
  `user_id` int(11) NULL DEFAULT NULL COMMENT '用户ID',
  `order_time` datetime(0) NULL DEFAULT NULL COMMENT '下单时间',
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '收货人姓名',
  `phone` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '联系电话',
  `addr` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '收货地址',
  `state` int(11) NULL DEFAULT NULL COMMENT '订单状态',
  `total` double NULL DEFAULT NULL COMMENT '总价',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user--id1`(`user_id`) USING BTREE,
  CONSTRAINT `user--id1` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 29 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of order
-- ----------------------------
INSERT INTO `order` VALUES (19, 1, '2020-06-14 02:23:21', 'nhy', '12312341234', '华中科技大学', 4, 13800);
INSERT INTO `order` VALUES (20, 1, '2020-06-14 02:24:13', 'nhy', '12312341234', '华中科技大学', 3, 13800);
INSERT INTO `order` VALUES (21, 1, '2020-06-14 02:33:26', 'nhy', '12312341234', '华中科技大学', 2, 12000);
INSERT INTO `order` VALUES (22, 1, '2020-06-15 13:58:42', 'nhy', '12312341234', 'hzkjdx', 1, 100);
INSERT INTO `order` VALUES (23, 2, '2020-06-16 02:54:55', 'nhy', '12312341234', 'wh', 1, 99.5);
INSERT INTO `order` VALUES (24, 2, '2020-06-17 12:57:40', 'nhy', '12312341234', '123', 3, 2290);
INSERT INTO `order` VALUES (25, 2, '2020-06-17 13:00:33', 'wzc', '12312341234', 'sd', 1, 1650);
INSERT INTO `order` VALUES (26, 1, '2020-06-17 13:11:32', 'lay', '12312341234', '1', 1, 7250);
INSERT INTO `order` VALUES (27, 10, '2020-06-18 03:53:03', 'wzc', '11111111111', 'sandon', 4, 25300);
INSERT INTO `order` VALUES (28, 10, '2020-06-18 03:53:56', 'wzc', '11111111111', 'sandon', 1, 120);
INSERT INTO `order` VALUES (29, 11, '2020-06-21 03:04:54', 'nhy', '12312341234', '123', 4, 6600);

-- ----------------------------
-- Table structure for order_item
-- ----------------------------
DROP TABLE IF EXISTS `order_item`;
CREATE TABLE `order_item`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `count` int(11) NULL DEFAULT NULL,
  `order_id` int(11) NULL DEFAULT NULL,
  `product_id` int(11) NULL DEFAULT NULL,
  `sub_total` double NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `order_id`(`order_id`) USING BTREE,
  INDEX `product_need`(`product_id`) USING BTREE,
  CONSTRAINT `order_id` FOREIGN KEY (`order_id`) REFERENCES `order` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `product_need` FOREIGN KEY (`product_id`) REFERENCES `product` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 36 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of order_item
-- ----------------------------
INSERT INTO `order_item` VALUES (19, 1, 19, 1, 12000);
INSERT INTO `order_item` VALUES (20, 1, 19, 3, 1800);
INSERT INTO `order_item` VALUES (21, 1, 20, 1, 12000);
INSERT INTO `order_item` VALUES (22, 1, 20, 3, 1800);
INSERT INTO `order_item` VALUES (23, 1, 21, 1, 12000);
INSERT INTO `order_item` VALUES (24, 1, 22, 10, 100);
INSERT INTO `order_item` VALUES (25, 1, 23, 7, 99.5);
INSERT INTO `order_item` VALUES (26, 1, 24, 8, 2290);
INSERT INTO `order_item` VALUES (27, 1, 25, 4, 1600);
INSERT INTO `order_item` VALUES (28, 1, 25, 5, 50);
INSERT INTO `order_item` VALUES (29, 1, 26, 3, 6600);
INSERT INTO `order_item` VALUES (30, 1, 26, 11, 650);
INSERT INTO `order_item` VALUES (31, 1, 27, 1, 11000);
INSERT INTO `order_item` VALUES (32, 1, 27, 2, 6100);
INSERT INTO `order_item` VALUES (33, 1, 27, 3, 6600);
INSERT INTO `order_item` VALUES (34, 1, 27, 4, 1600);
INSERT INTO `order_item` VALUES (35, 2, 28, 6, 120);
INSERT INTO `order_item` VALUES (36, 1, 29, 3, 6600);

-- ----------------------------
-- Table structure for product
-- ----------------------------
DROP TABLE IF EXISTS `product`;
CREATE TABLE `product`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `csid` int(11) NULL DEFAULT NULL,
  `desc` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `image` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `is_hot` int(11) NULL DEFAULT NULL,
  `market_price` double NULL DEFAULT NULL,
  `pdate` datetime(0) NULL DEFAULT NULL,
  `shop_price` double NULL DEFAULT NULL,
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `content` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `csid`(`csid`) USING BTREE,
  CONSTRAINT `csid` FOREIGN KEY (`csid`) REFERENCES `classification` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 23 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of product
-- ----------------------------
INSERT INTO `product` VALUES (1, 2, '对于 MacBook，我们给自己设定了一个几乎不可能实现的目标：在有史以来最为轻盈纤薄的 Mac 笔记本电脑上，打造全尺寸的使用体验。这就要求我们不仅要令其更为纤薄轻巧，还要更加出色。在新款 MacBook 上，我们新配备了第七代 Intel Core m3、i5 和 i7 处理器，使处理性能提升最高可达 20%1，此外还采用了速度提升最高可达 50% 的固态硬盘存储2。', '/mall/admin/product/img/1.jpg', 1, 13888, '2020-06-24 13:34:08', 12000, '苹果 (Apple） 2020新款 MacBook Pro 苹果笔记本电脑 15英寸Bar/i7/16G/256G/灰/H32', NULL);
INSERT INTO `product` VALUES (2, 11, '证书编号：2019011606222162\r\n证书状态：有效\r\n产品名称：TD-LTE \r\n数字移动电话机3C\r\n规格型号：A2223\r\n(电源适配器可选：A1443 输出：5.0VDC 1A)\r\n产品名称：Apple/苹果 iPhone 11\r\nApple型号: iPhone 11\r\n机身颜色: 红色 白色 黑色 黄色 绿色 紫色存储容量: 64GB 128GB 256GB', '/mall/admin/product/img/2.jpg', 1, 8799, '2020-06-17 13:00:52', 6100, 'Apple 苹果 iPhone 11 手机 深空灰色 全网通 256GB', NULL);
INSERT INTO `product` VALUES (3, 2, 'CCC证书编号: 2017010902948411\r\n网络类型: WIFI 4G\r\n品牌: Apple/苹果\r\n型号: iPad Pro\r\n内存容量: 256GB 64GB 512MB\r\n存储容量: 64GB 128GB 256GB 512GB 1TB\r\n成色: 全新\r\n售后服务: 全国联保\r\n分辨率: 2388 x 1668 分辨率', '/mall/admin/product/img/3.jpg', 1, 7318, '2020-06-17 13:02:46', 6600, 'Apple Ipad Pro 2020 平板电脑 256G', NULL);
INSERT INTO `product` VALUES (4, 11, '商品名称：AppleMWP22CH/A商品编号：100009691096商品毛重：240.00g商品产地：以官网信息为准连接类型：无线（蓝牙）佩戴方式：真无线用途：降噪耳机', '/mall/admin/product/img/4.jpg', 1, 2200, '2020-06-16 02:36:40', 1600, 'Apple AirPods Pro 主动降噪无线蓝牙耳机', NULL);
INSERT INTO `product` VALUES (5, 6, '名著：礼记', '/mall/admin/product/img/5.jpg', 1, 199, '2020-06-16 02:35:04', 50, '礼记', NULL);
INSERT INTO `product` VALUES (6, 6, 'C语言学习', '/mall/admin/product/img/6.jpg', 1, 80, '2020-06-16 02:34:30', 60, 'C程序设计', NULL);
INSERT INTO `product` VALUES (7, 6, '四大名著：红楼梦、水浒传、西游记、三国演义', '/mall/admin/product/img/7.jpg', 1, 125, '2020-06-16 02:22:14', 99.5, '四大名著', NULL);
INSERT INTO `product` VALUES (8, 13, '商品名称：安普里奥·阿玛尼AR1981商品编号：100005535176商品毛重：488.00g商品产地：中国广东货号：AR1981表扣：针扣表带：其它表盘：圆形机芯：自动机械适用人群：男士表径：41-43mm风格：商务，休闲风，时尚，其它防水：30米表底：透窗表壳：不锈钢', '/mall/admin/product/img/8.jpg', 1, 3790, '2020-06-16 02:33:19', 2290, '阿玛尼（ Emporio Armani）手表 商务时尚全自动机械镂空男士机械腕表', NULL);
INSERT INTO `product` VALUES (9, 13, '商品名称：丹尼尔惠灵顿DW女表商品编号：5398175商品毛重：300.00g商品产地：广东深圳机芯：石英适用人群：女士风格：休闲风，时尚，极简防水：生活防水', '/mall/admin/product/img/9.jpg', 0, 496, '2020-06-18 03:55:51', 269, '丹尼尔惠灵顿 DanielWellington DW手表 女表金边钢带28mm简约白盘欧美学生石英表', NULL);
INSERT INTO `product` VALUES (10, 7, '商品名称：Satchi沙驰女鞋新款牛漆皮尖头细跟高跟鞋商品编号：10143276220店铺： 沙驰旗舰店商品毛重：0.82kg商品产地：中国大陆货号：C243039D鞋面材质：头层牛皮（除牛反绒）适用季节：春秋 鞋跟形状：细跟鞋跟高度：高跟(6-8cm)流行元素：皮带扣款式：高跟鞋风格：欧美风鞋头款式：尖头图案：纯色内里材质：羊皮', '/mall/admin/product/img/10.jpg', 1, 139, '2020-06-16 02:31:36', 100, 'Satchi沙驰女鞋新款牛漆皮尖头细跟高跟鞋', NULL);
INSERT INTO `product` VALUES (11, 7, '商品名称：胜道运动Adidas阿迪达斯男女鞋EQT运动鞋耐磨透气休闲跑步鞋B96491 B96491 42.5商品编号：29000487558店铺： 胜道运动旗舰店商品毛重：1.0kg货号：B96491适用人群：男士上市时间：2018年夏季功能：透气闭合方式：系带适合路面：其它', '/mall/admin/product/img/11.jpg', 1, 900, '2020-06-16 02:12:27', 650, '阿迪达斯男女鞋EQT运动鞋耐磨透气休闲跑步鞋', NULL);
INSERT INTO `product` VALUES (12, 7, '商品名称：阿迪达斯官网 adidas 三叶草 EQT BASK ADV V2男鞋经典运动鞋FW4256 晶白/信号珊瑚粉/1号黑色 41(255mm)商品编号：69365692616店铺： adidas官方旗舰店商品毛重：1.0kg货号：FW4256鞋面材质：其它适用人群：男士鞋底材质：其它上市时间：2020年春季款式：低帮选购热点：经典款闭合方式：系带功能：其它', '/mall/admin/product/img/12.jpg', 1, 558, '2020-06-16 02:20:56', 450, 'adidas 三叶草 EQT BASK ADV V2男鞋经典运动鞋FW4256', NULL);
INSERT INTO `product` VALUES (22, 17, '品牌: 瓦袖货号: WTT097基础风格: 青春流行上市年份季节: 2020年夏季厚薄: 常规销售渠道类型: 纯电商(只在线上销售)材质成分: 棉100%', '/mall/admin/product/img/13.jpg', 0, 65, '2020-06-16 09:07:41', 38, '夏季短袖T恤男潮牌ins宽松五分袖韩版潮流男士简约半袖体恤上衣服', NULL);

-- ----------------------------
-- Table structure for shop_car
-- ----------------------------
DROP TABLE IF EXISTS `shop_car`;
CREATE TABLE `shop_car`  (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID',
  `userid` int(11) NULL DEFAULT NULL COMMENT '用户ID',
  `productid` int(11) NULL DEFAULT NULL COMMENT '商品ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_id`(`userid`) USING BTREE,
  INDEX `product_id`(`productid`) USING BTREE,
  CONSTRAINT `product_id` FOREIGN KEY (`productid`) REFERENCES `product` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `user_id` FOREIGN KEY (`userid`) REFERENCES `user` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 32 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of shop_car
-- ----------------------------
INSERT INTO `shop_car` VALUES (31, 10, 22);

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `username` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `phone` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `email` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `addr` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`, `name`) USING BTREE,
  INDEX `id`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 12 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, '123', '123', '123', '1234567891-', '2265940560@qq.com', 'whwh');
INSERT INTO `user` VALUES (2, 'nhy', 'nhy', '123', '1234567891-', '2265940561@qq.com', 'hzkjdx');
INSERT INTO `user` VALUES (10, 'wzcwzc', 'wzc', '123', '12312312312', '111@qq.com', 'sandon');
INSERT INTO `user` VALUES (11, 'nhy', 'test', '123', '12312312312', '123@qq.com', 'test');

-- ----------------------------
-- Procedure structure for test
-- ----------------------------
DROP PROCEDURE IF EXISTS `test`;
delimiter ;;
CREATE PROCEDURE `test`()
BEGIN
DECLARE a,b int DEFAULT 5;
insert into T(s1) VALUES (a);
select s1*a from T where s1>=b;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
