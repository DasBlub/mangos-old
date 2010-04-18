ALTER TABLE `characters` ADD `deleteInfos_Account` INT( 11 ) UNSIGNED NULL;
ALTER TABLE `characters` ADD `deleteInfos_Name` varchar(12) character set utf8 collate utf8_unicode_ci default NULL;
ALTER TABLE `characters` ADD `deleteDate` BIGINT(20) NULL DEFAULT NULL;
