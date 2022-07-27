# DeathCounter
Hello! This rudimentary c++ program is a death counter for any game.
It records the enemy name and timestamp into two csv files, log and count. 

.exe Program:
- Type name, then enter to record death.
- Prefix name with asterisk * for victory
- q to quit
- p to print stats

Columns in count.csv:
- Name
- Deaths
- Wins

Columns in log.csv: (each session has newline break)
- Name of enemy (case-sensitive)
- Date
- Timestamp of death/victory
- Time since starting session
