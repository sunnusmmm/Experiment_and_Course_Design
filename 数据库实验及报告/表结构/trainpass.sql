/*
 Navicat Premium Data Transfer

 Source Server         : First
 Source Server Type    : MySQL
 Source Server Version : 80016
 Source Host           : localhost:3306
 Source Schema         : lab2

 Target Server Type    : MySQL
 Target Server Version : 80016
 File Encoding         : 65001

 Date: 12/05/2020 22:26:03
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for trainpass
-- ----------------------------
DROP TABLE IF EXISTS `trainpass`;
CREATE TABLE `trainpass`  (
  `TID` int(11) NOT NULL,
  `SNo` smallint(6) NOT NULL,
  `SID` int(11) NOT NULL,
  `STime` datetime(0) NULL DEFAULT NULL,
  `ATime` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`TID`, `SNo`) USING BTREE,
  INDEX `SID_idx`(`SID`) USING BTREE,
  INDEX `TID`(`TID`) USING BTREE,
  CONSTRAINT `SID` FOREIGN KEY (`SID`) REFERENCES `station` (`SID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
