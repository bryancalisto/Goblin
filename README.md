# Goblin (El Duende)
Simple Windows "malware" that I made for learning purposes. It does not do "bad" stuff apart from the specified.
<br/>
<br/>
<p>The program jokes with the next actions, frequently and randomly:</p>

<ul>
  <li>Shuffles the desktop icons (but saves current state before).</li>
  <li>Reverts the desktop icons shuffle.</li>
  <li>Modifies system date (OS's, not RTC). Works only if run as admin.</li>
  <li>Displays a cmd window for a few seconds and then hides it</li>
  <li>Creates files with strange names on desktop (empty files).</li>
  <li>Deletes the strange-named files previously created.</li>
  <li>Heats the CPU by executing some heavy processes for a few seconds.</li>
</ul>
<br/>
<p>The first time it runs, it creates a copy of itself and stores it in %HOMEPATH% and also creates a registry entry to run that copy on boot.</p>
<p>From there on, it will run everytime the system boots.</p>
<br/>
<p>Also notice:</p>
<ul>
  <li>WD labels it as trojan.</li>
  <li>It lacks of obfuscation.</li>
  <li>Joking interval and other parameters (e.g. number of created files, CPU heat duration) should be adjusted to own preferences.</li>
</ul>
