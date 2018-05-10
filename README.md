# Lab-Efficient-Algorithms
## test.py
test wird aufgerufen mit:
python test.py `<task-ordner>`

Das Skript sucht nach den Dateien
  * test.cases
  * test.results
  * build/main          -- optional
  * build/main.class    -- optional
  * main.py             -- optional

und führt die, die es findet mit den gegebenen TestCases aus (im Moment nur den einen, aber die Aufgaben scheinen eh so designed zu sein das eine Datei reichen wird.)
Das ist nur ne vorläufige Version, bei Bedarf ruhig anpassen.

Es wird jetzt auch ein file namens diff.html generiert, der line-by-line die Unterschiede zwischen Expected und given output darstellt - kann manchmal ganz nützlich sein.
