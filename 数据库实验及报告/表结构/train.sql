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

 Date: 13/05/2020 10:22:26
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for train
-- ----------------------------
DROP TABLE IF EXISTS `train`;
CREATE TABLE `train`  (
  `TID` int(11) NOT NULL,
  `SDate` date NOT NULL,
  `TName` char(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `SStationID` int(11) NOT NULL,
  `AStationID` int(11) NOT NULL,
  `STime` datetime(0) NOT NULL,
  `ATime` datetime(0) NOT NULL,
  PRIMARY KEY (`TID`) USING BTREE,
  UNIQUE INDEX `TName_UNIQUE`(`TName`, `SDate`) USING BTREE,
  INDEX `SStationID_idx`(`SStationID`) USING BTREE,
  INDEX `AStationID_idx`(`AStationID`) USING BTREE,
  CONSTRAINT `AStationID` FOREIGN KEY (`AStationID`) REFERENCES `station` (`SID`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `SStationID` FOREIGN KEY (`SStationID`) REFERENCES `station` (`SID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
