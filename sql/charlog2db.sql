DROP TABLE IF EXISTS `charlog`;
CREATE TABLE IF NOT EXISTS `charlog` (
  `guid` int(11) NOT NULL,
  `charname` varchar(40) NOT NULL,
  `account` int(11) NOT NULL,
  `timestamp` timestamp NOT NULL,
  `ip` varchar(40) NOT NULL,
  `action` int(1) NOT NULL,
  PRIMARY KEY  (`guid`,`account`,`timestamp`,`action`)
);
