DELETE FROM mangos_string WHERE entry IN (1016, 1017, 1018, 1019, 1020, 1021, 1022);
INSERT INTO mangos_string (entry, content_default) VALUES
 (1016, '| GUID       | Name                 | Account                      | Delete Date         |')
,(1017, '| %10u | %20s | %15s (%10u) | %19s |')
,(1018, '==========================================================================================')
,(1019, 'No characters found.')
,(1020, 'Restoring the following characters:')
,(1021, 'Deleting the following characters:')
,(1022, 'ERROR: You can only assign a new name if you have only selected a single character!')
;
