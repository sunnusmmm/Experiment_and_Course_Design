DROP TABLE IF EXISTS `station`;	-- 主键 SID
CREATE TABLE `station`  (
  `SID` int(11) NOT NULL,
  `SName` char(20) NOT NULL,
  `CityName` char(20) NOT NULL,
  PRIMARY KEY (`SID`) USING BTREE
);

DROP TABLE IF EXISTS `train`;	-- 	主键 TID 外键 SStationID—— `station`.(`SID`)、AStationID——`station`.(`SID`)
CREATE TABLE `train`  (
  `TID` int(11) NOT NULL,
  `SDate` date NOT NULL,
  `TName` char(20) NOT NULL,
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
);

DROP TABLE IF EXISTS `trainpass`;	-- 主键 (TID、SNo) 外键 SID——`station`.(`SID`)
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
);

DROP TABLE IF EXISTS `passenger`;	-- 主键 PCardID
CREATE TABLE `passenger`  (
  `PCardID` char(18) NOT NULL,
  `PName` char(20) NOT NULL,
  `Sex` int(11) NOT NULL,
  `age` smallint(6) NOT NULL,
  PRIMARY KEY (`PCardID`) USING BTREE
);

DROP TABLE IF EXISTS `taketrainrecord`;	-- 主键 RID 外键PCardID——`passenger`.(`PCardID`)、SStationID1——`trainpass`.(`SID`)、AStationID1——`trainpass`.(`SID`)、TID——`trainpass`.(`TID`)
CREATE TABLE `taketrainrecord`  (
  `RID` int(11) NOT NULL,
  `PCardID` char(18) NOT NULL,
  `TID` int(11) NOT NULL,
  `SStationID` int(11) NOT NULL,
  `AStationID` int(11) NOT NULL,
  `CarrigeID` smallint(6) NOT NULL,
  `SeatRow` smallint(6) NOT NULL,
  `SeatNo` char(1) NOT NULL,
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
);

DROP TABLE IF EXISTS `diagnoserecord`;	-- 主键 DID
CREATE TABLE `diagnoserecord`  (
  `DID` int(11) NOT NULL,
  `PCardID` char(18) NOT NULL,
  `DDay` date NOT NULL,
  `DStatus` smallint(6) NOT NULL,
  `FDay` date NOT NULL,
  PRIMARY KEY (`DID`) USING BTREE
);

DROP TABLE IF EXISTS `traincontactor`; -- 主键 (CDate、CCardID、DStatus、PCardID)
CREATE TABLE `traincontactor`  (
  `CDate` date NOT NULL,
  `CCardID` char(18) NOT NULL,
  `DStatus` smallint(6) NOT NULL,
  `PCardID` char(18) NOT NULL,
  PRIMARY KEY (`CDate`, `CCardID`, `DStatus`, `PCardID`) USING BTREE
);