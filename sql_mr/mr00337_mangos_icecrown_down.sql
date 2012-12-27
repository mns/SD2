-- Forge of souls
-- UPDATE `creature_template` SET `ScriptName`='mob_soul_storm', `AIName` ='' WHERE `entry`=; 

UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_jaina_and_sylvana_FSintro' where `entry` IN (37597, 37596);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_jaina_and_sylvana_FSextro' where `entry` IN (38160, 38161);
UPDATE `creature_template` SET `scale` = 0.8 WHERE `entry` IN (37221, 36955, 36658, 37225, 37223, 37226, 37554);
UPDATE `creature_template` SET `npcflag`='3' where `entry` IN (38160, 38161);
UPDATE `creature_template` SET `equipment_id` = 1290 WHERE `entry` = 37554;

-- Pit of saron
UPDATE `scripted_areatrigger` SET `ScriptName`='at_tyrannus' WHERE `entry`='5578';

-- Boss
DELETE FROM `gameobject` WHERE `id` = 201885;
UPDATE `creature_template` SET `ScriptName`='boss_ick' WHERE `entry`=36476;
UPDATE `creature_template` SET `ScriptName`='boss_krick' WHERE `entry`=36477;
UPDATE `creature_template` SET `ScriptName`='mob_explosive_orb' WHERE `entry`=36610;
UPDATE `creature_template` SET `ScriptName`='boss_rimefang' WHERE `entry`=36661;
UPDATE `creature_template` SET `ScriptName`='npc_colapsing_icicle' WHERE `entry`=36847;

UPDATE `creature_template` SET `ScriptName`='boss_scourgelord_tyrannus', `AIName` ='' WHERE `entry`=36658;

UPDATE `creature_template` SET `equipment_id` = '2011', `unit_flags` = '0' WHERE `entry` = 36658;
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14' WHERE `entry` = 36661;

-- npc
UPDATE `creature_template` SET `ScriptName`='npc_slyvanas_jaina_pos_start' WHERE `entry` in (36993, 36990);
UPDATE `creature_template` SET `ScriptName`='npc_slyvanas_jaina_pos_end' WHERE `entry` in (38188, 38189);
UPDATE `creature_template` SET `ScriptName`='npc_martin_gorkun' WHERE `entry` in (37591, 37592);
update `creature` set spawnMask = 0 where `id` in (37591, 37592, 38188, 38189, 36731);
update `creature` set spawnMask = 0 where `guid` in (123745, 123584, 123548, 123585);

UPDATE `gameobject_template` SET `data10` = 1 WHERE `entry` = 196485;

-- spells
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('69347', '1', '36794');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70521', '1', '37581');

DELETE FROM `spell_target_position` WHERE `id` = 70860;
INSERT INTO `spell_target_position` VALUES
(70860, 631, 529.302, -2124.49, 840.857, 3.1765);

-- Halls of reflection
UPDATE `instance_template` SET `ScriptName` = 'instance_halls_of_reflection' WHERE map=668;

UPDATE `gameobject_template` SET `faction`='1375' WHERE `entry` IN (197341, 202302, 201385, 201596);

UPDATE `creature_template` SET `speed_walk`='1.5', `speed_run`='2.0' WHERE `entry` IN (36954, 37226);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_jaina_and_sylvana_HRintro' WHERE `entry` IN (37221, 37223);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='boss_falric' WHERE `entry` IN (38112);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='boss_marwyn' WHERE `entry` IN (38113);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='boss_lich_king_intro_hor' WHERE `entry` IN (36954);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='boss_lich_king_hr' WHERE `entry` IN (37226);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_jaina_and_sylvana_HRextro' WHERE `entry` IN (36955, 37554);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_undead_hor' WHERE `entry` IN (36940,36941,37069);
UPDATE `creature_template` SET `scale`='0.8' WHERE `entry` IN (37221, 36955);
UPDATE `creature_template` SET `equipment_id` = 1290 WHERE `entry` = 37554;
UPDATE `creature_template` SET `equipment_id`='0' WHERE `entry`=36954;
UPDATE `creature_template` SET `scale`='0.8' WHERE `entry` IN (36658, 37225, 37223, 37226, 37554);
UPDATE `creature_template` SET `unit_flags`='768', `type_flags`='268435564' WHERE `entry` IN (38177, 38176, 38173, 38172, 38567, 38175);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_frostworn_general' WHERE `entry`=36723;
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_spiritual_reflection' WHERE `entry`=37068;

REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70464', '1', '36881');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('69708', '1', '37226');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70194', '1', '37226');

REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70224', '1', '37014');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70225', '1', '37014');

REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('69431', '1', '37497');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('69431', '1', '37496');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('69431', '1', '37588');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('69431', '1', '37584');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('69431', '1', '37587');

REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(135341, 38112, 668, 3, 1, 0, 0, 5276.81, 2037.45, 709.32, 5.58779, 604800, 0, 0, 377468, 0, 0, 0);
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(135342, 38113, 668, 3, 1, 0, 0, 5341.72, 1975.74, 709.32, 2.40694, 604800, 0, 0, 539240, 0, 0, 0);

REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(14531739, 201596, 668, 1, 128, 5275.28, 1694.23, 786.147, 0.981225, 0, 0, 0.471166, 0.882044, 25, 0, 1);

DELETE from `creature` WHERE `id`=36955;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(151040, 36955, 668, 3, 128, 0, 0, 5547.27, 2256.95, 733.011, 0.835987, 7200, 0, 0, 252000, 881400, 0, 0);

DELETE from `creature` WHERE `id`=37554;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(151041, 37554, 668, 3, 64, 0, 0, 5547.27, 2256.95, 733.011, 0.835987, 7200, 0, 0, 252000, 881400, 0, 0);

UPDATE `creature` SET `position_x` = 5551.29, `position_y` = 2261.33, `position_z` = 733.012, `orientation` = 4.0452 WHERE `id` = 37226;

UPDATE `creature_template` SET `modelid_1` = 11686, `modelid_2` = 11686, `modelid_3` = 11686, `modelid_4` = 11686 WHERE `entry` IN (37014,37704);

DELETE FROM `gameobject` WHERE `id` IN (201385,201596,202079);

UPDATE `gameobject_template` SET `faction` = '114',`data0` = '0' WHERE `gameobject_template`.`entry` IN (197341,197342,197343);
UPDATE `gameobject` SET `state` = 1 WHERE `id` IN (197342,197343);

-- offlike way for icewalls operation
DELETE from `creature` WHERE `id`=37014;
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_queldelar_hor' where `entry` IN (37158);
DELETE from `creature` WHERE `map` = 668 AND `id` IN (37221,37223,37554,36955);

-- Captains chest (override)
DELETE FROM `gameobject` WHERE `id` IN (202212,201710,202337,202336);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(972562, 202212, 668, 1, 65535,  5241.047, 1663.4364, 784.295166, 0.54, 0, 0, 0, 0, -604800, 100, 1),
(972563, 201710, 668, 1, 65535,  5241.047, 1663.4364, 784.295166, 0.54, 0, 0, 0, 0, -604800, 100, 1),
(972564, 202337, 668, 2, 65535,  5241.047, 1663.4364, 784.295166, 0.54, 0, 0, 0, 0, -604800, 100, 1),
(972565, 202336, 668, 2, 65535,  5241.047, 1663.4364, 784.295166, 0.54, 0, 0, 0, 0, -604800, 100, 1);
-- Dalaran portal (override)
UPDATE `gameobject` SET `phaseMask` = 65535, `orientation` = 0, `rotation2` = 0, `rotation3` = 0, `spawntimesecs` = -604800, `animprogress` = 100 WHERE `id` = 202079 AND `map` = 668;

/* Original Icewalls from YTDB
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(3485, 201385, 668, 3, 1, 5540.39, 2086.48, 731.066, 1.00057, 0, 0, 0.479677, 0.877445, 604800, 100, 1),
(3438, 201385, 668, 3, 1, 5494.3, 1978.27, 736.689, 1.0885, 0, 0, 0.517777, 0.855516, 604800, 100, 1),
(3386, 201385, 668, 3, 1, 5434.27, 1881.12, 751.303, 0.923328, 0, 0, 0.445439, 0.895312, 604800, 100, 1),
(3383, 201385, 668, 3, 1, 5323.61, 1755.85, 770.305, 0.784186, 0, 0, 0.382124, 0.924111, 604800, 100, 1);
*/

-- EVENT AI

-- ICC trash mobs from Xfurry
-- ###########
-- LOWER SPIRE
-- ###########

-- The Damned (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id`=3701101;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3701101,37011,0,0,100,30,10000,15000,10000,15000,11,70960,0,0,0,0,0,0,0,0,0,0, 'The Dammed  - cast Bone Flurry');
DELETE FROM `creature_ai_scripts` WHERE `id`=3701102;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3701102,37011,6,0,100,30,0,0,0,0,11,70961,0,0,0,0,0,0,0,0,0,0, 'The Dammed  - cast Shattred Bones');
-- Nerub'ar Broodkeeper (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3672501, 3672502, 3672503, 3672504);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3672501,36725,10,0,100,31,1,60,0,0,38,0,0,0,0,0,0,0,0,0,0,0, 'Nerubar broodkeeper - set aggressive'),
(3672502,36725,0,0,100,31,5000,7000,5000,7000,11,70965,4,0,0,0,0,0,0,0,0,0, 'Nerubar Broodkeeper - crypt scarabs'),
(3672503,36725,14,0,100,31,50,30,8000,13000,11,36725,6,0,0,0,0,0,0,0,0,0, 'Nerubar broodkeeper - dark mending'),
(3672504,36725,0,0,100,31,7000,11000,7000,11000,11,70980,4,0,0,0,0,0,0,0,0,0, 'Nerubar broodkeeper - web wrap');
-- Deathbound Ward (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3700701, 3700702, 3700703);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3700701,37007,10,0,100,31,1,80,0,0,38,0,0,0,0,0,0,0,0,0,0,0, 'Deathbound ward - set aggressive'),
(3700702,37007,0,0,100,31,5000,7000,5000,7000,11,71021,1,0,0,0,0,0,0,0,0,0, 'Deathbound ward - saber lash'),
(3700703,37007,0,0,100,31,15000,20000,20000,30000,11,71022,0,0,0,0,0,0,0,0,0,0, 'Deathbound ward - disrupting shout');

-- #####################
-- ORATORY OF THE DAMMED
-- #####################

-- Deathspeaker Attendant (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3681101, 3681102, 3681103);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3681101,36811,0,0,100,31,3000,5000,6000,8000,11,69387,4,0,0,0,0,0,0,0,0,0, 'Deathspeaker attendant - shadow bolt'),
(3681102,36811,0,0,100,11,10000,15000,10000,15000,11,69355,0,0,0,0,0,0,0,0,0,0, 'Deathspeaker attendant - shadow nova 10'),
(3681103,36811,0,0,100,21,10000,15000,10000,15000,11,71106,0,0,0,0,0,0,0,0,0,0, 'Deathspeaker attendant - shadow nova 25');
-- Deathspeaker Disciple (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3680701, 3680702, 3680703, 3680704);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3680701,36807,0,0,100,31,3000,6000,7000,10000,11,69387,4,0,0,0,0,0,0,0,0,0, 'Deathspeaker disciple - shadow bolt'),
(3680702,36807,16,0,100,31,69391,30,5000,9000,11,69391,6,0,0,0,0,0,0,0,0,0, 'Deathspeaker disciple - dark blessing'),
(3680703,36807,14,0,100,11,50,50,7000,11000,11,69389,6,0,0,0,0,0,0,0,0,0, 'Deathspeaker disciple - shadow mend 10'),
(3680704,36807,14,0,100,21,50,50,7000,11000,11,71107,6,0,0,0,0,0,0,0,0,0, 'Deathspeaker disciple - shadow mend 25');
-- Deathspeaker Servant (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3680501, 3680502, 3680503, 3680504, 3680505);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3680501,36805,0,0,100,31,7000,10000,7000,10000,11,69405,4,0,0,0,0,0,0,0,0,0, 'Deathspeaker Servant - consuming shadows'),
(3680502,36805,0,0,100,11,4000,7000,4000,7000,11,69576,4,0,0,0,0,0,0,0,0,0, 'Deathspeaker servant - chaos bolt 10'),
(3680503,36805,0,0,100,21,4000,7000,4000,7000,11,71108,4,0,0,0,0,0,0,0,0,0, 'Deathspeaker servant - chaos bolt 25'),
(3680504,36805,0,0,100,11,7000,13000,7000,13000,11,69404,4,0,0,0,0,0,0,0,0,0, 'Deathspeaker servant - curse of agony 10'),
(3680505,36805,0,0,100,21,7000,13000,7000,13000,11,71112,4,0,0,0,0,0,0,0,0,0, 'Deathspeaker servant - curse of agony 25');

-- ################
-- RAMPART OF SKULL
-- ################

-- Frenzied Abomination (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3754601, 3754602);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3754601,37546,0,0,100,31,3000,5000,3000,5000,11,70191,1,0,0,0,0,0,0,0,0,0, 'Frenzied abomination - abomination cleave'),
(3754602,37546,2,0,100,30,10,9,0,0,11,70371,0,0,0,0,0,0,0,0,0,0, 'Frenzied abomination - enrage');
-- Spire Minion (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3754501, 3754502);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3754501,37545,0,0,100,31,3000,6000,3000,6000,11,70396,1,0,0,0,0,0,0,0,0,0, 'Spire minion - ghoul slash'),
(3754502,37545,0,0,100,31,30000,30000,30000,30000,11,70363,0,0,0,0,0,0,0,0,0,0, 'Spire minion - cannibalize');

-- ###########
-- PLAGUEWORKS
-- ###########

-- Blighted Abomination (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3702201, 3702202, 3702203);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3702201,37022,0,0,100,31,2000,5000,2000,5000,11,40504,1,0,0,0,0,0,0,0,0,0, 'Blighted abomination - cleave'),
(3702202,37022,0,0,100,31,7000,15000,20000,30000,11,71150,0,0,0,0,0,0,0,0,0,0, 'Blighted abomination - plague cloud'),
(3702203,37022,0,0,100,31,5000,10000,10000,15000,11,71140,4,0,0,0,0,0,0,0,0,0, 'Blighted abomination - scourge hook');
-- Plague Scientist (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` IN (3702301, 3702302, 3702303);
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3702301,37023,0,0,100,31,10000,10000,10000,10000,11,71103,4,0,0,0,0,0,0,0,0,0, 'Plague scientist - combobulating spray'),
(3702302,37023,0,0,100,31,8000,11000,8000,11000,11,73079,4,0,0,0,0,0,0,0,0,0, 'Plague scientist - plague blast'),
(3702303,37023,0,0,100,31,15000,20000,15000,20000,11,69871,6,0,0,0,0,0,0,0,0,0, 'Plague scientist - plague stream');

-- Vengefull fleshreaper (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id`=3703801;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3703801,37038,0,0,100,31,5000,10000,5000,10000,11,71164,5,0,0,0,0,0,0,0,0,0, 'Vengefull fleshreaper - leaping face maul');

-- #############
-- CRIMSON HALLS
-- #############

-- Darkfallen Archmage (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3766401 AND 3766407;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3766401,37664,0,0,100,11,5000,10000,30000,35000,11,70408,0,0,0,0,0,0,0,0,0,0, 'Darkfallen archmage - amplify magic 10'),
(3766402,37664,0,0,100,21,5000,10000,30000,35000,11,72336,0,0,0,0,0,0,0,0,0,0, 'Darkfallen archmage - amplify magic 25'),
(3766403,37664,0,0,100,11,7000,11000,7000,11000,11,70407,0,0,0,0,0,0,0,0,0,0, 'Darkfallen archmage - blast wave 10'),
(3766404,37664,0,0,100,21,7000,11000,7000,11000,11,71151,0,0,0,0,0,0,0,0,0,0, 'Darkfallen archmage - blast wave 25'),
(3766405,37664,0,0,100,11,9000,13000,9000,13000,11,70409,4,0,0,0,0,0,0,0,0,0, 'Darkfallen archmage - fireball 10'),
(3766406,37664,0,0,100,21,9000,13000,9000,13000,11,71153,4,0,0,0,0,0,0,0,0,0, 'Darkfallen archmage - fireball 25'),
(3766407,37664,0,0,100,31,10000,10000,10000,10000,11,70410,5,0,0,0,0,0,0,0,0,0, 'Darkfallen archmage - polymorph spider');
-- Darkfallen Blood Knight (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3759501 AND 3759503;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3759501,37595,4,0,100,6,0,0,0,0,11,71736,0,0,0,0,0,0,0,0,0,0, 'Darkfallen blood knight - vampiric aura'),
(3759502,37595,0,0,100,31,5000,9000,5000,9000,11,70450,1,0,0,0,0,0,0,0,0,0, 'Darkfallen blood knight - blood mirror'),
(3759503,37595,0,0,100,31,3000,6000,3000,6000,11,70437,1,0,0,0,0,0,0,0,0,0, 'Darkfallen blood knight - unholy strike');
-- Darkfallen Noble (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3766301 AND 3766303;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3766301,37663,0,0,100,31,7000,11000,7000,11000,11,70645,4,0,0,0,0,0,0,0,0,0, 'Darkfallen noble - chains of shadow'),
(3766302,37663,0,0,100,11,3000,6000,3000,6000,11,72960,4,0,0,0,0,0,0,0,0,0, 'Darkfallen noble - shadow bolt 10'),
(3766303,37663,0,0,100,21,3000,6000,3000,6000,11,72961,4,0,0,0,0,0,0,0,0,0, 'Darkfallen noble - shadow bolt 25');
-- Darkfallen Advisor (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3757101 AND 3757104;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3757101,37571,0,0,100,11,5000,9000,5000,9000,11,72057,4,0,0,0,0,0,0,0,0,0, 'Darkfallen advisor - lich slap 10'),
(3757102,37571,0,0,100,21,5000,9000,5000,9000,11,72421,4,0,0,0,0,0,0,0,0,0, 'Darkfallen advisor - lich slap 25'),
(3757103,37571,16,0,100,31,72066,40,10000,20000,11,72066,6,0,0,0,0,0,0,0,0,0, 'Darkfallen advisor - shroud of spell warding'),
(3757104,37571,16,0,100,31,72065,50,10000,20000,11,72065,6,0,0,0,0,0,0,0,0,0, 'Darkfallen advisor - shroud of protection');
-- Darkfallen Lieutenant (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3766501 AND 3766503;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3766501,37665,0,0,100,11,5000,7000,5000,7000,11,70435,1,0,0,0,0,0,0,0,0,0, 'Darkfallen lieutenant - rend flesh 10'),
(3766502,37665,0,0,100,21,5000,7000,5000,7000,11,71154,1,0,0,0,0,0,0,0,0,0, 'Darkfallen lieutenant - rend flesh 25'),
(3766503,37665,0,0,100,31,5000,7000,20000,25000,11,70423,1,0,0,0,0,0,0,0,0,0, 'Darkfallen lieutenant - vampiric curse');
-- Darkfallen Tactician (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3766601 AND 3766603;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3766601,37666,0,0,100,31,5000,7000,10000,13000,11,70432,1,0,0,0,0,0,0,0,0,0, 'Darkfallen tactitian - blood sap'),
(3766602,37666,0,0,100,31,7000,10000,7000,10000,11,70437,1,0,0,0,0,0,0,0,0,0, 'Darkfallen tactitian - unholy strike'),
(3766603,37666,4,0,100,6,0,0,0,0,11,70431,0,0,0,0,0,0,0,0,0,0, 'Darkfallen tactitian - shadowstep');
-- Darkfallen Commander (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3766201 AND 3766203;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3766201,37662,4,0,100,6,0,0,0,0,11,70750,0,0,0,0,0,0,0,0,0,0, 'Darkfallen commander - battle shout'),
(3766202,37662,0,0,100,11,3000,5000,5000,7000,11,70449,5,0,0,0,0,0,0,0,0,0, 'Darkfallen commander - vampire rush 10'),
(3766203,37662,0,0,100,21,3000,5000,5000,7000,11,71155,5,0,0,0,0,0,0,0,0,0, 'Darkfallen commander - vampire rush 25');

-- #########
-- FROSTWING
-- #########

-- Frostwing whelp (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3753201 AND 3753203;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3753201,37532,0,0,100,31,5000,7000,10000,13000,11,71350,4,0,0,0,0,0,0,0,0,0, 'Frostwing whelp - focus fire'),
(3753202,37532,0,0,100,11,4000,5000,4000,5000,11,71361,4,0,0,0,0,0,0,0,0,0, 'Frostwing whelp - frost blast 10'),
(3753203,37532,0,0,100,21,4000,5000,4000,5000,11,71362,4,0,0,0,0,0,0,0,0,0, 'Frostwing whelp - frost blast 25');
-- Ymirjar battle maiden (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3713201 AND 3713202;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3713201,37132,0,0,100,31,4000,6000,10000,11000,11,71258,0,0,0,0,0,0,0,0,0,0, 'Ymirjar battle maiden - adrenaline rush'),
(3713202,37132,0,0,100,31,5000,7000,5000,7000,11,71257,3,0,0,0,0,0,0,0,0,0, 'Ymirjar battle maiden - barbaric strike');
-- Ymirjar deathbringer (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3812501 AND 3812507;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3812501,38125,0,0,100,31,4000,6000,6000,8000,11,71298,4,0,0,0,0,0,0,0,0,0, 'Ymirjar deathbringer - banish'),
(3812502,38125,0,0,100,11,7000,13000,15000,20000,11,71299,0,0,0,0,0,0,0,0,0,0, 'Ymirjar deathbringer - deaths embrace 10'),
(3812503,38125,0,0,100,21,7000,13000,15000,20000,11,71300,0,0,0,0,0,0,0,0,0,0, 'Ymirjar deathbringer - deaths embrace 25'),
(3812504,38125,0,0,100,11,4000,7000,4000,7000,11,71296,4,0,0,0,0,0,0,0,0,0, 'Ymirjar deathbringer - shadow bolt 10'),
(3812505,38125,0,0,100,21,4000,7000,4000,7000,11,71297,4,0,0,0,0,0,0,0,0,0, 'Ymirjar deathbringer - shadow bolt 25'),
(3812506,38125,16,0,100,31,69929,30,35000,50000,11,69929,6,0,0,0,0,0,0,0,0,0, 'Ymirjar deathbringer - spirit steam'),
(3812507,38125,0,0,100,31,20000,25000,25000,30000,11,71303,0,0,0,0,0,0,0,0,0,0, 'Ymirjar deathbringer - summon ymirjar');
-- Ymirjar huntress (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3713401 AND 3713405;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3713401,37134,0,0,100,31,5000,10000,7000,14000,11,71249,0,0,0,0,0,0,0,0,0,0, 'Ymirjar huntress - ice trap'),
(3713402,37134,0,0,100,31,8000,13000,10000,15000,11,71251,0,0,0,0,0,0,0,0,0,0, 'Ymirjar huntress - rapid shot'),
(3713403,37134,0,0,100,31,2000,4000,2000,4000,11,71253,4,0,0,0,0,0,0,0,0,0, 'Ymirjar huntress - shoot'),
(3713404,37134,0,0,100,31,6000,8000,7000,10000,11,71252,4,0,0,0,0,0,0,0,0,0, 'Ymirjar huntress - volley'),
(3713405,37134,4,0,100,6,0,0,0,0,11,71705,0,0,0,0,0,0,0,0,0,0, 'Ymirjar huntress - summon warhawk');
-- Ymirjar frostbinder (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3712701 AND 3712703;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3712701,37127,0,0,100,31,7000,10000,7000,10000,11,71306,5,0,0,0,0,0,0,0,0,0, 'Ymirjar frostbinder - twisted winds'),
(3712702,37127,0,0,100,31,15000,20000,15000,20000,11,71274,5,0,0,0,0,0,0,0,0,0, 'Ymirjar frostbinder - frozen orb'),
(3712703,37127,4,0,100,6,0,0,0,0,11,71270,0,0,0,0,0,0,0,0,0,0, 'Ymirjar frostbinder - arctic chill');

#-- ###############
#-- VALITHRIA EVENT
#-- ###############

#-- Grottnous abomination
#UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`=37886;
#DELETE FROM `creature_ai_scripts` WHERE `id`=3788601;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3788601,37886,0,0,100,3,7000,13000,7000,13000,11,70633,0,0,0,0,0,0,0,0,0,0, 'Gluttnous abomination - gut spray 10n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3788602;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3788602,37886,0,0,100,5,7000,13000,7000,13000,11,71283,0,0,0,0,0,0,0,0,0,0, 'Gluttnous abomination - gut spray 25n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3788603;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3788603,37886,0,0,100,9,7000,13000,7000,13000,11,72025,0,0,0,0,0,0,0,0,0,0, 'Gluttnous abomination - gut spray 10h');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3788604;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3788604,37886,0,0,100,17,7000,13000,7000,13000,11,72026,0,0,0,0,0,0,0,0,0,0, 'Gluttnous abomination - gut spray 25h');
#-- Blistering Zombies
#UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`=37934;
#DELETE FROM `creature_ai_scripts` WHERE `id`=3793401;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3793401,37934,4,0,100,31,0,0,0,0,11,70749,0,0,0,0,0,0,0,0,0,0, 'Blistering zombies - corrosion');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3793402;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3793402,37934,6,0,100,3,0,0,0,0,11,70744,0,0,0,0,0,0,0,0,0,0, 'Blistering zombies - acid burst 10n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3793403;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3793403,37934,6,0,100,5,0,0,0,0,11,71733,0,0,0,0,0,0,0,0,0,0, 'Blistering zombies - acid burst 25n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3793404;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3793404,37934,6,0,100,9,0,0,0,0,11,72017,0,0,0,0,0,0,0,0,0,0, 'Blistering zombies - acid burst 10h');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3793405;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3793405,37934,6,0,100,17,0,0,0,0,11,72018,0,0,0,0,0,0,0,0,0,0, 'Blistering zombies - acid burst 25h');
#-- Suppresser
#UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`=37863;
#DELETE FROM `creature_ai_scripts` WHERE `id`=3786301;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3786301,37863,4,0,100,31,0,0,0,0,11,70588,1,0,0,0,0,0,0,0,0,0, 'Suppresser - suppression');
#-- Blazing Skeleton
#UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`=36791;
#DELETE FROM `creature_ai_scripts` WHERE `id`=3679101;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3679101,36791,0,0,100,3,5000,10000,5000,10000,11,70754,4,0,0,0,0,0,0,0,0,0, 'Blazin skeleton - fireball 10n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3679102;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3679102,36791,0,0,100,5,5000,10000,5000,10000,11,71748,4,0,0,0,0,0,0,0,0,0, 'Blazin skeleton - fireball 25n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3679103;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3679103,36791,0,0,100,9,5000,10000,5000,10000,11,72023,4,0,0,0,0,0,0,0,0,0, 'Blazin skeleton - fireball 10h');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3679104;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3679104,36791,0,0,100,17,5000,10000,5000,10000,11,72024,4,0,0,0,0,0,0,0,0,0, 'Blazin skeleton - fireball 25h');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3679105;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3679105,36791,0,0,100,11,10000,15000,10000,15000,11,69325,0,0,0,0,0,0,0,0,0,0, 'Blazin skeleton - lay waste 10');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3679106;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3679106,36791,0,0,100,21,10000,15000,10000,15000,11,71730,0,0,0,0,0,0,0,0,0,0, 'Blazin skeleton - lay waste 10');
-- Mana void
-- UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`=38068;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=38068);
-- INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
-- (3806801,38068,4,0,100,31,0,0,0,0,11,71085,0,0,0,0,0,0,0,0,0,0, 'Mana void - mana void aura');
#UPDATE `creature_template` SET `modelid1` = 11686 WHERE `entry` = 38068;
#-- Risen archmage
#UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`=37868;
#DELETE FROM `creature_ai_scripts` WHERE `id`=3786801;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3786801,37868,0,0,100,3,7000,11000,7000,11000,11,70759,0,0,0,0,0,0,0,0,0,0, 'Risen archmage - frostbolt volley 10n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3786802;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3786802,37868,0,0,100,5,7000,11000,7000,11000,11,71889,0,0,0,0,0,0,0,0,0,0, 'Risen archmage - frostbolt volley 25n');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3786803;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3786803,37868,0,0,100,9,7000,11000,7000,11000,11,72015,0,0,0,0,0,0,0,0,0,0, 'Risen archmage - frostbolt volley 10h');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3786804;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3786804,37868,0,0,100,17,7000,11000,7000,11000,11,72016,0,0,0,0,0,0,0,0,0,0, 'Risen archmage - frostbolt volley 25h');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3786805;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3786805,37868,0,0,100,11,25000,30000,25000,30000,11,71179,0,0,0,0,0,0,0,0,0,0, 'Risen archmage - mana void 10');
#DELETE FROM `creature_ai_scripts` WHERE `id`=3786806;
#INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
#(3786806,37868,0,0,100,21,25000,30000,25000,30000,11,71741,0,0,0,0,0,0,0,0,0,0, 'Risen archmage - mana void 10');

-- ############
-- SVALNA EVENT
-- ############

-- Captain Rupert (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3712501 AND 3712503;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3712501,37125,0,0,100,31,5000,7000,7000,11000,11,71787,4,0,0,0,0,0,0,0,0,0, 'Captain Rupert - fel bomb'),
(3712502,37125,0,0,100,31,7000,9000,9000,13000,11,71594,4,0,0,0,0,0,0,0,0,0, 'Captain Rupert - machine gun'),
(3712503,37125,0,0,100,31,10000,13000,15000,17000,11,71786,4,0,0,0,0,0,0,0,0,0, 'Captain Rupert - rocket');
-- Captain Grondel (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3712401 AND 3712404;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3712401,37124,0,0,100,31,10000,10000,10000,10000,11,71553,5,0,0,0,0,0,0,0,0,0, 'Captain Groundel - charge'),
(3712402,37124,0,0,100,31,5000,10000,10000,15000,11,71554,3,0,0,0,0,0,0,0,0,0, 'Captain Groundel - sunder armor'),
(3712403,37124,0,0,100,31,5000,7000,5000,7000,11,71552,1,0,0,0,0,0,0,0,0,0, 'Captain Groundel - mortal strike'),
(3712404,37124,0,0,100,31,5000,9000,10000,15000,11,71785,4,0,0,0,0,0,0,0,0,0, 'Captain Groundel - conflagration');
-- Captain Brandon (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3712301 AND 3712304;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3712301,37123,0,0,100,31,10000,10000,10000,10000,11,71549,1,0,0,0,0,0,0,0,0,0, 'Captain Brandon - crusader strike'),
(3712302,37123,2,0,100,30,25,24,0,0,11,71550,0,0,0,0,0,0,0,0,0,0, 'Captain Brandon - divine shield'),
(3712303,37123,0,0,100,31,5000,8000,7000,10000,11,71784,4,0,0,0,0,0,0,0,0,0, 'Captain Brandon - hammer of betrayal'),
(3712304,37123,0,0,100,31,7000,10000,8000,12000,11,71551,4,0,0,0,0,0,0,0,0,0, 'Captain Brandon - judgement of command');
-- Captain Arnath (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3712201 AND 3712207;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3712201,37122,14,0,100,31,50,30,5000,10000,11,71595,6,0,0,0,0,0,0,0,0,0, 'Captain Arnath - flash heal'),
(3712202,37122,0,0,100,21,15000,20000,20000,25000,11,14515,4,0,0,0,0,0,0,0,0,0, 'Captain Arnath - dominate mind'),
(3712203,37122,16,0,100,31,71548,30,30000,35000,11,71548,6,0,0,0,0,0,0,0,0,0, 'Captain Arnath - power shield'),
(3712204,37122,0,0,100,3,5000,10000,9000,15000,11,71546,4,0,0,0,0,0,0,0,0,0, 'Captain Arnath - smite 10n'),
(3712205,37122,0,0,100,5,5000,10000,9000,15000,11,71547,4,0,0,0,0,0,0,0,0,0, 'Captain Arnath - smite 25n'),
(3712206,37122,0,0,100,9,5000,10000,9000,15000,11,71778,4,0,0,0,0,0,0,0,0,0, 'Captain Arnath - smite 10h'),
(3712207,37122,0,0,100,17,5000,10000,9000,15000,11,71779,4,0,0,0,0,0,0,0,0,0, 'Captain Arnath - smite 25h');
-- Crok and Svalna need SD2 script
-- this is just a basic of spells
-- Crok Scourgebane (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3712901 AND 3712904;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3712901,37129,0,0,100,31,5000,7000,7000,9000,11,71489,1,0,0,0,0,0,0,0,0,0, 'Crock Scrougebane - deathstrike'),
(3712902,37129,0,0,100,31,7000,9000,10000,12000,11,71488,1,0,0,0,0,0,0,0,0,0, 'Crock Scrougebane - scourgestrike'),
(3712903,37129,0,0,100,21,10000,15000,10000,15000,11,71490,4,0,0,0,0,0,0,0,0,0, 'Crock Scrougebane - deathcoil'),
(3712904,37129,4,0,100,6,0,0,0,0,39,30,0,0,0,0,0,0,0,0,0,0, 'Crock Scrougebane - call for help');
-- Svalna (need compare with YTDB)
DELETE FROM `creature_ai_scripts` WHERE `id` BETWEEN 3712601 AND 3712604;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES 
(3712601,37126,4,0,100,6,0,0,0,0,11,71465,0,0,0,0,0,0,0,0,0,0, 'Sister Svalna - divine surge'),
(3712602,37126,0,0,100,11,15000,20000,20000,25000,11,71468,0,0,0,0,0,0,0,0,0,0, 'Sister Svalna - aether burst 10'),
(3712603,37126,0,0,100,21,15000,20000,20000,25000,11,71469,0,0,0,0,0,0,0,0,0,0, 'Sister Svalna - aether burst 25'),
(3712604,37126,0,0,100,31,25000,30000,60000,70000,11,70196,5,0,11,71463,0,0,0,0,0,0, 'Sister Svalna - sprear');
