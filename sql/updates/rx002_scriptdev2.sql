DELETE FROM script_texts WHERE entry BETWEEN -1568087 AND -1568086;
INSERT INTO script_texts (entry,content_default,sound,TYPE,LANGUAGE,emote,COMMENT) VALUES
-- Harkor
(-1568086,'Finally freed',2725,0,0,4,'SAY_HARKOR_FREED'),
(-1568087,'Want to thank you for rescuing me',0,0,0,0,'SAY_HARKOR_THANK');

DELETE FROM script_waypoint WHERE entry = 23790;
INSERT INTO script_waypoint (entry, pointid, location_x, location_y, location_z, waittime, point_comment) VALUES
(23790, 0, -142.24, 1337.17, 48.174, 0, ''),
(23790, 1, -136.21, 1334.06, 48.174, 1000, ''),
(23790, 2, -136.21, 1334.06, 48.174, 4000, 'Emote use standing'),
(23790, 3, -136.21, 1334.06, 48.174, 1000, 'unlock object - Emote none - speed run'),
(23790, 4, -130.58, 1340.65, 48.174, 0, ''),
(23790, 5, -111.57, 1345.37, 40.83, 0, ''),
(23790, 6, -79.80, 1378.67, 40.75, 0, ''),
(23790, 7, -79.64, 1395.80, 27.18, 0, '');

-- Harkor
DELETE FROM script_waypoint WHERE entry = 23999;
INSERT INTO script_waypoint (entry, pointid, location_x, location_y, location_z, waittime, point_comment) VALUES
(23999, 0, 298.7605, 1464.95, 81.5753, 3000, 'SAY_HARKOR_FREED'),
(23999, 1, 298.7605, 1464.95, 81.5753, 3000, 'SAY_HARKOR_THANK'),
(23999, 2, 302.2797, 1462.846, 81.57086, 0, ''),
(23999, 3, 306.3771, 1463.949, 81.58128, 2000, 'EMOTE_ONESHOT_KNEEL'),
(23999, 4, 306.3771, 1463.949, 81.58128, 2000, 'GO despwn 186623 , SetEquipmentSlots'),
(23999, 5, 304.3857, 1465.72, 81.58634, 1000, ''),
(23999, 6, 304.3857, 1465.72, 81.58634, 2000, ''),
(23999, 7, 304.3857, 1465.72, 81.58634, 1000, ''),
(23999, 8, 306.61, 1457.25, 81.52, 0, ''),
(23999, 9, 320.06, 1445.15, 74.35, 0, ''),
(23999, 10, 351.09, 1421.8, 74.28, 0, ''),
(23999, 11, 336.07, 1391.52, 74.33, 0, ''),
(23999, 12, 315.26, 1384.89, 57.40, 0, '');

DELETE FROM script_waypoint WHERE entry = 24024;
INSERT INTO script_waypoint (entry, pointid, location_x, location_y, location_z, waittime, point_comment) VALUES
(24024, 0, -74.16, 1159.86, 5.49, 0, ''),
(24024, 1, -86.05, 1132.41, 5.6, 0, ''),
(24024, 2, -83.67, 1125.1, 5.6, 0, ''),
(24024, 3, -81.04, 1125.12, 5.64, 1000, ''),
(24024, 4, -81.04, 1125.12, 5.64, 4000, 'Emote use standing'),
(24024, 5, -81.04, 1125.12, 5.64, 1000, 'unlock object - Emote none - speed run'),
(24024, 6, -100.43, 1103.40, 5.55, 0, ''),
(24024, 7, -110.4, 1095.61, 0, 0, '');

DELETE FROM script_waypoint WHERE entry = 24001;
INSERT INTO script_waypoint (entry, pointid, location_x, location_y, location_z, waittime, point_comment) VALUES
(24001, 0, 383.67, 1089.85, 6.04, 0, ''),
(24001, 1, 339.55, 1091.72, 6.38, 1000, ''),
(24001, 2, 339.55, 1091.72, 6.38, 5000, 'Casting Fireball'),
(24001, 3, 343.66, 1143.42, 6.32, 1000, ''),
(24001, 4, 343.66, 1143.42, 6.32, 5000, 'Casting Fireball'),
(24001, 5, 419.19, 1143.12, 5.60, 1000, ''),
(24001, 6, 420.27, 1089.76, 6.46, 1000, ''),
(24001, 7, 420.27, 1089.76, 6.46, 5000, 'Casting Fireball'),
(24001, 8, 369.59, 1089.97, 6.47, 0, ''),
(24001, 9, 369.44, 1078.38, 6.48, 0, ''),
(24001, 10, 369.44, 1075.42, 9.62, 0, ''),
(24001, 11, 369.78, 1035.86, 10.1, 0, '');
