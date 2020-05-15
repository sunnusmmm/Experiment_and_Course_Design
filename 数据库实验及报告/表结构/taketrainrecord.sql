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

 Date: 12/05/2020 22:25:41
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for taketrainrecord
-- ----------------------------
DROP TABLE IF EXISTS `taketrainrecord`;
CREATE TABLE `taketrainrecord`  (
  `RID` int(11) NOT NULL,
  `PCardID` char(18) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `TID` int(11) NOT NULL,
  `SStationID` int(11) NOT NULL,
  `AStationID` int(11) NOT NULL,
  `CarrigeID` smallint(6) NOT NULL,
  `SeatRow` smallint(6) NOT NULL,
  `SeatNo` char(1) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `SStatus` int(11) NOT NULL,
  PRIMARY KEY (`RID`) USING BTREE,
  INDEX `PCardID_idx`(`PCardID`) USING BTREE,
  INDEX `TID_idx`(`TID`) USING BTREE,
  INDEX `AStationID1`(`AStationID`) USING BTREE,
  INDEX `SStationID1`(`SStationID`) USING BTREE,
  CONSTRAINT `AStationID1` FOREIGN KEY (`AStationID`) REFERENCES `trainpass` (`SID`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `PCardID` FOREIGN KEY (`PCardID`) REFERENCES `passenger` (`PCardID`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `SStationID1` FOREIGN KEY (`SStationID`) REFERENCES `trainpass` (`SID`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `TID` FOREIGN KEY (`TID`) REFERENCES `trainpass` (`TID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
