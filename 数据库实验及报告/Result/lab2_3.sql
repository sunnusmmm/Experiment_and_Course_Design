-- (1)查询确诊者“李玉兰”在发病前14天内的乘车记录
SELECT
	passenger.PName,
	passenger.PCardID,
	train.TID,
	train.TName,
	train.SDate,
	diagnoserecord.FDay 
FROM
	passenger,
	taketrainrecord,
	train,
	diagnoserecord 
WHERE
	passenger.PName = "李玉兰" 
	AND passenger.PCardID = taketrainrecord.PCardID 
	AND taketrainrecord.SStatus != 2
	AND taketrainrecord.TID = train.TID 
	AND passenger.PCardID = diagnoserecord.PCardID 
	AND DATEDIFF( diagnoserecord.FDay, train.SDate ) <= 14 AND DATEDIFF( diagnoserecord.FDay, train.SDate ) >= 0;
-- (2)查询所有从城市“武汉”出发的乘客乘列车所到达的城市名
SELECT DISTINCT
	( CityName ) 
FROM
	station 
WHERE	-- 是否从武汉出发 以及 乘坐状态
	SID IN ( SELECT AStationID FROM taketrainrecord WHERE SStationID IN ( SELECT SID FROM station WHERE CityName = "武汉" ) AND SStatus != 2 );
-- (3)计算每位新冠患者从发病到确诊的时间间隔（天数）及患者身份信息，并将结果按照发病时间天数的降序排列

SELECT * FROM (( SELECT PCardID, DATEDIFF( DDay, FDay ) AS Days FROM diagnoserecord WHERE DStatus = 1) AS A	-- //这里同时输出了发病天数
	LEFT JOIN passenger ON A.PCardID = passenger.PCardID 
) 
ORDER BY
	Days DESC;
-- (4)查询“2020-01-22”从“武汉”发出的所有列车
SELECT
	*
FROM
	train 
WHERE
	SStationID IN ( SELECT SID FROM station WHERE CityName = "武汉" ) 
	AND SDate = "2020-01-22";
-- (5)查询“2020-01-22”途经“武汉”的所有列车
SELECT
	TID,
	TName 
FROM
	train -- //从train中获取列车名
WHERE
	TID IN (
	SELECT DISTINCT	-- 	//查询trainpass中在“2020-01-22”途径武汉的列车TID
		( TID ) 
	FROM
		trainpass 
	WHERE
		SNo != 1 -- //不是起点站
		AND SID IN ( SELECT SID FROM station WHERE CityName = "武汉" ) 
	AND datediff( STime, "2020-01-22" ) = 0 
	);
-- (6)查询“2020-01-22”从武汉离开的所有乘客的身份证号、所到达的城市、到达日期
-- //从taketrainrecord查询出"2020-01-22"从武汉站出发的列车以及乘客身份证，然后根据查询到的乘车记录表中的到达站编号查询trainpass中到达站的时间，从station中查询到列车名。输出身份证、到达城市名、到达时间
SELECT PCardID,CityName,STime from 
(select PCardID,A.TID,AStationID from 
((select RID,PCardID,taketrainrecord.TID,SStationID,AStationID from taketrainrecord where SStationID in (select SID from station where CityName = "武汉") AND SStatus != 2)AS A LEFT JOIN trainpass ON  trainpass.TID = A.TID AND trainpass.SID = A.SStationID ) 
WHERE DATEDIFF("2020-01-22",ATime) = 0) 
AS B LEFT JOIN trainpass ON  trainpass.TID = B.TID AND trainpass.SID = B.AStationID LEFT JOIN station ON B.AStationID = station.SID;
-- (7)统计“2020-01-22” 从武汉离开的所有乘客所到达的城市及达到各个城市的武汉人员数
SELECT
	s2.CityName,
	COUNT(*) 
FROM
	taketrainrecord,
	station s1,
	station s2,
	train,
	trainpass
WHERE
	s1.CityName = '武汉' 
	AND taketrainrecord.TID = train.TID
	AND taketrainrecord.SStatus != 2
	AND s1.SID = taketrainrecord.SStationID 
	AND s2.SID = taketrainrecord.AStationID 
	AND trainpass.TID = taketrainrecord.TID
	AND trtrainpass.SID = taketrainrecord.SStationID
	AND DATE(trtrainpass.STime) = "2020-01-22"
GROUP BY
	s2.CityName;
-- (8)查询2020年1月到达武汉的所有人员
-- //从taketrainrecord中查询到达站为武汉车站的乘车记录，再连接trainpass中查询到达站点日期在一月份的记录，根据已经查找到的信息，从passager中查出人员信息
SELECT * FROM passenger WHERE PCardID IN 
(SELECT PCardID FROM (SELECT RID,PCardID,TID,AStationID FROM taketrainrecord WHERE AStationID IN 
(SELECT SID FROM station WHERE CityName = "武汉")) AS A LEFT JOIN trainpass ON A.TID = trainpass.TID AND A.AStationID = trainpass.SID 
WHERE STime BETWEEN "2020-01-01" AND "2020-02-01");
-- (9)查询2020年1月乘车途径武汉的外地人员（身份证非“420”开头）
SELECT
	* 
FROM
	passenger 
WHERE
	PCardID IN (
	SELECT
		PCardID 
	FROM
		taketrainrecord 
	WHERE
--        //查询taketrainrecord中乘坐过途径武汉的列车的乘客
		TID IN (
		SELECT
			TID 
		FROM
			train 
		WHERE
-- 			//查询train中一月份从武汉发出的列车TID
			TID IN (
			SELECT DISTINCT
				( TID ) 
			FROM
				trainpass 
			WHERE
				SNo != 1 
			AND SID IN ( SELECT SID FROM station WHERE CityName = "武汉" )) 
			AND ( STime BETWEEN "2020-01-01" AND "2020-02-01" ) = 1 
		) 
		AND SStatus != 2 
	AND PCardID NOT LIKE "420%" 
	);
-- (10)统计“2020-01-22”乘坐过‘G007’号列车的新冠患者在火车上的密切接触乘客人数（每位新冠患者的同车厢人员都算同车密切接触）
SELECT
	a.PCardID,
	(
	SELECT
		count(*) -- 与该患者密切接触的人数
	FROM
		taketrainrecord E
	WHERE
		A.TID = E.TID -- 与患者乘相同列车
		AND E.SStatus != 2 -- 乘坐车辆
		AND A.CarrigeID = E.CarrigeID -- 相同车厢
		AND A.PCardID != E.PCardID -- 除去本人
	) AS NUM 
FROM
	taketrainrecord A,
	diagnoserecord B,
	train C,
	trainpass D 
WHERE
	A.PCardID = B.PCardID 
	AND A.TID = C.TID 
	AND A.TID = D.TID 
	AND A.SStationID = D.SID 
	AND B.DStatus = 1 
	AND A.SStatus != 2 
	AND DATE( D.STime ) = "2020-01-22" 
	AND C.TName LIKE "G1013";
-- (11)查询一趟列车的一节车厢中有3人及以上乘客被确认患上新冠的列车名、出发日期，车厢号
SELECT
	A.TID,
	A.TName,
	B.CarrigeID
FROM
	train A,(
	SELECT
		TID,
		COUNT(*) AS NUM,
        CarrigeID
	FROM
		taketrainrecord 
	WHERE
		PCardID IN ( SELECT PCardID FROM diagnoserecord WHERE DStatus = 1 )
	GROUP BY
		TID,
		CarrigeID 
	) B -- // 以TID和CarrigeID为组查找列车车厢中感染人数
WHERE
	A.TID = B.TID 
	AND B.NUM >= 3; -- //条件查询
-- (12)查询没有感染任何周边乘客的新冠乘客的身份证号、姓名、乘车日期
SELECT
	* 
FROM
	diagnoserecord 
WHERE
	diagnoserecord.PCardID NOT IN (
	SELECT
		traincontactor.PCardID 
	FROM
		traincontactor 
WHERE
	traincontactor.DStatus = 1)
-- (13)查询到达 “北京”、或“上海”，或“广州”（即终点站）的列车名，要求where子句中除了连接条件只能有一个条件表达式
SELECT TID,TName  FROM train LEFT JOIN station ON train.AStationID = station.SID WHERE CityName IN ("北京","上海", "广州");
-- (14)查询“2020-01-22”从“武汉站”出发，然后当天换乘另一趟车的乘客身份证号和首乘车次号，结果按照首乘车次号降序排列，同车次则按照乘客身份证号升序排列
SELECT
    PCardID,
    TName
FROM
-- 	//将表trainpass、station、train、taketrainrecord连接起来查找符合条件的用户
    taketrainrecord a,
    train,
	trainpass,
	station
WHERE	-- 	//查询条件
    station.sname = '武汉'
	AND train.TID = a.TID
	AND station.SID= a.SStationID
	AND trainpass.TID = a.TID
	AND trainpass.SID = a.SStationID
    AND DATE(trainpass.STime) = '2020-01-22'
    AND a.SStatus !=2
    AND EXISTS (	--  //是否存在转车
        SELECT
            *
        FROM
            taketrainrecord b,
            trainpass c
        WHERE
            a.PCardID = b.PCardID
			AND c.TID = b.TID
            AND c.SID = b.SStationID
            AND b.SStationID = a.AStationID
            AND DATE(c.STime) = '2020-01-22'
            AND c.STime > trainpass.STime
            AND b.SStatus != 2
    )
ORDER BY
    TName DESC,
    PCardID ASC;
-- (15)查询所有新冠患者的身份证号，姓名及其2020年以来所乘坐过的列车名、发车日期，要求即使该患者未乘坐过任何列车也要列出来
SELECT
	A.PName,
	A.PCardID,
	train.TID,
	train.SDate 
FROM
	(
-- //查询新冠患者的信息及其乘车记录
	SELECT
		passenger.PCardID,
		passenger.PName,
		diagnoserecord.DStatus 
	FROM
		passenger,
		diagnoserecord 
	WHERE
		diagnoserecord.DStatus = 1 
		AND passenger.PCardID = diagnoserecord.PCardID 
	) AS A	-- //连接taketrainrecord、train查询2020年来乘坐过的列车名发车日期
	LEFT JOIN taketrainrecord ON A.PCardID = taketrainrecord.PCardID
	LEFT JOIN train ON taketrainrecord.TID = train.TID AND
	DATEDIFF( train.SDate, "2020-01-01" ) >= 0;
-- (16)查询所有发病日期相同而且确诊日期相同的病患统计信息，包括：发病日期、确诊日期和患者人数，结果按照发病日期降序排列的前提下再按照确诊日期降序排列
SELECT
	DDay,
	FDay,
	count(*)
FROM
	diagnoserecord 
WHERE
	DStatus = 1
	GROUP BY	-- 	//以发病日期和确诊日期分类
	DDay,
	FDay 
ORDER BY
	DDay DESC,
	FDay DESC;