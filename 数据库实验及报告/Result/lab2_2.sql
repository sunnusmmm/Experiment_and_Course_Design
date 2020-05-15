-- **1**）分别用一条sql语句完成对乘车记录表基本的增、删、改的操作；
-- ```mysql
INSERT INTO TABLE A (FIELD 1, FIELD 2) VALUES (FIELD 1, FIELD 2);
DELETE FROM TABLE A [WHERE Clause];
UPDATE TABLE A SET FIELD 1 = new-value1, FIELD 2 = new-value2 [WHERE Clause];
-- ```

-- **2**）批处理操作
-- 将乘车记录表中的从武汉出发的乘客的乘车记录插入到一个新表WH_TakeTrainRecord中。
-- ```mysql
-- //表不存在时 创建表并插入查询数据
CREATE TABLE WH_TakeTrainRecord AS SELECT * FROM taketrainrecord WHERE SStationID IN (SELECT SID FROM station WHERE CityName = "武汉");
-- ```
-- ```mysql
-- //表已存在
INSERT INTO WH_TakeTrainRecord SELECT * FROM taketrainrecord WHERE SStationID IN (SELECT SID FROM station WHERE CityName = "武汉");
-- ```

-- **3**）数据导入导出
-- 通过查阅DBMS资料学习数据导入导出功能，并将任务2.1所建表格的数据导出到操作系统文件，然后再将这些文件的数据导入到相应空表。
-- **4**）观察性实验
-- 建立一个关系，但是不设置主码，然后向该关系中插入重复元组，然后观察在图形化交互界面中对已有数据进行删除和修改时所发生的现象。
-- > 当不设主码时，表中可以存在数据项相同的数据存在，例表WH_TakeTrainRecord设置为无主码，插入两条RID为1的数据，当改变RID=1的数据时，两条数据都会被改变，删除同；
-- **5**）创建视图
-- 创建一个新冠确诊病人的乘火车记录视图，其中的属性包括：身份证号、姓名、年龄、乘坐列车编号、发车日期、车厢号，席位排号，席位编号。按身份证号升序排序，如果身份证号一致，按发车日期降序排序（注意，如果病人买了票但是没坐车，不计入在内）。
-- ```mysql
CREATE VIEW patient_view as 
(SELECT passenger.PName,passenger.PCardID,passenger.age,taketrainrecord.TID,train.STime,CarrigeID,SeatRow,SeatNo 
FROM passenger,diagnoserecord,taketrainrecord,train 
WHERE passenger.PCardID = diagnoserecord.PCardID AND diagnoserecord.DStatus = 1 
AND passenger.PCardID = taketrainrecord.PCardID AND taketrainrecord.TID = train.TID 
AND taketrainrecord.SStatus != 2 ORDER BY PCardID ,STime DESC);
-- ```

-- **6**）触发器实验
-- 编写一个触发器，用于实现以下完整性控制规则：
-- 1) 当新增一个确诊患者时，若该患者在发病前14天内有乘车记录，则将其同排及前后排乘客自动加入“乘客紧密接触者表”，其中：接触日期为乘车日期。
CREATE TRIGGER `Insert_Update` AFTER UPDATE ON `diagnoserecord` FOR EACH ROW  BEGIN 
		IF(new.	DStatus = 1) THEN
		INSERT INTO traincontactor
		SELECT Train.SDate,TRD1.PCardID,2,new.PCardID	-- 更新的数据PCardID
		FROM Train,TakeTrainRecord TRD1 -- TRD1是密切接触者
		WHERE Train.TID = TRD1.TID
			AND EXISTS( -- 乘车约束，TRD1的患者14天内乘过车，和该患者在同一车厢，在该患者前排后排，同排的乘客加入密切接触者表
				SELECT * FROM 
				TakeTrainRecord TRD2  -- 插入诊断表确诊的患者
				WHERE new.PCardID = TRD2.PCardID 
					AND TRD1.TID = TRD2.TID -- 找到该患者
					AND TRD2.CarrigeID = TRD1.CarrigeID
					AND TRD1.SeatRow IN (TRD2.SeatRow,TRD2.SeatRow + 1 ,TRD2.SeatRow - 1)
					AND DATEDIFF(new.FDay,Train.SDate) <= 14	-- 对比日期
					AND DATEDIFF(new.FDay,Train.SDate) >= 0
					AND TRD1.SStatus != 2 AND TRD2.SStatus != 2
					AND TRD1.PCardID <> new.PCardID	-- 不是自身
			);
		END IF;
		END;
-- 2) 当一个紧密接触者被确诊为新冠时，从“乘客紧密接触者表”中修改他的状态为“1”。
CREATE TRIGGER `Syn`
ON `diagnoserecord` FOR EACH ROW
AFTER UPDATE 
BEGIN 
	UPDATE `traincontactor` SET DStatus = new.DStatus;
END