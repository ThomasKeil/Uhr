<?php

function convert($input) {
  $search =  ["\""];
  $replace = ['\"'];
  $input = str_replace($search, $replace, $input);

  $search =  ["ä",    "ö",    "ü",    "ß",    "Ä",    "Ö",   "Ü"];
  $replace = ['\xe4" "', '\xf6" "', '\xfc" "', '\xdf" "', '\xc4" "','\xd6" "', '\xdc" "'];
  return str_replace($search, $replace, $input);

}

$past_dates = [
  "standesamtlich" => "02.02.2018 21:00",
  "kirchlich" => "22.09.2018 15:00"
];


$periods = [
  [
    "period" => 1,
    "name" => "Die Papierhochzeit",
    "text" => "Der Grundgedanke hinter dieser Bezeichnung ist, dass die Ehe noch frisch und dünn wie Papier ist. Zwar fühlen sich die meisten Paare schon sehr stark verbunden, doch könnten \"widrige Umstände\" die Ehe immer noch auflösen wie Nässe das Papier.\n Die Papierhochzeit ist einer der Hochzeitstage der meist in trauter Zweisamkeit gefeiert wird, um die Erinnerungen an die gemeinsame Zeit und den Tag der Trauung noch einmal wach zurufen."
    ],
  [
    "period" => 2,
    "name" => "Die Baumwollenhochzeit",
    "text" => "Das Brautpaar hat die ersten Höhen und Tiefen der Ehe hinter sich und kann mit diesen gut umgehen. Dadurch festigt sich der neue Bund und das Paar fühlt sich geborgen. Der Name Baumwollhochzeit entstand, weil Baumwolle weich ist, gut wärmt und damit die Geborgenheit in einer guten Ehe darstellt."
    ],
  [
    "period" => 3,
    "name" => "Die Lederne Hochzeit",
    "text" => "Leder ist widerstandsfähig und verlässlich. Daher soll bei der Ledernen Hochzeit gefeiert werden, dass sich die Ehepartner kennen und lieben - sowohl die schönen als auch die weniger schönen Seiten. Sie haben gelernt mit den Stimmungen des Partners umzugehen und den anderen so zu nehmen, wie er ist."
    ],
  [
    "period" => 4,
    "name" => "Die Seiden Hochzeit",
    "text" => "Ein nicht all zu bekannter Hochzeitstag und trotzdem wichtig genug um genannt zu werden. Dieser Tag wird gerne im kleinen Kreis verbracht und dazu genutzt, sich die Hochzeitsfotos noch einmal anzuschauen und ein bisschen in Erinnerung zu schwelgen. Falls doch größer gefeiert wird, bietet es sich an Seidenelemente mit in die Dekoration einzubauen. Eine Seidene Tischdecke mit passenden Servietten aus Seide und um alles abzurunden ein paar hübsche Seidenblumen, ganz getreu dem Motto."
    ],
  [
    "period" => 5,
    "name" => "Die Hölzerne Hochzeit",
    "text" => "Holz ist stark, beständig und stabil. Nach fünf Ehejahren wird in vielen Fällen auch die Ehe so sein. Das ist die Aussage der Hölzernen Hochzeit. So wie das Holz soll auch die Ehe in den nächsten Jahren immer weiter wachsen und immer kräftiger werden. Die Hölzerne Hochzeit ist das erste runde Jubiläum der Hochzeitstage."
    ],
  [
    "period" => 6,
    "name" => "Die Zinn Hochzeit",
    "text" => "Wie Zinn sollte auch die Ehe von Zeit zu Zeit ein bisschen aufgeputzt und poliert werden. Das verleiht neuen Glanz und neuen Schwung. Weil Zinn sehr weich und  formbar ist, steht es sinnbildlich  für die Formbarkeit der Ehe. Nutzen Sie diesen Tag und probieren sie etwas Neues aus. Beispielsweise festigen Fallschirmsprünge, Wanderurlaube oder andere Aktivitäten das Miteinander und bringen Spaß und außergewöhnliche Erinnerungen."
    ],
  [
    "period" => 7,
    "name" => "Die Kupferne Hochzeit",
    "text" => "Die Ehe glänzt nach sieben Jahren nicht mehr so neu, wie am ersten Tag. Aber unter der Schicht der Jahre liegt noch immer das \"Schöne\" und \"Wahre\". Aus der Verliebtheit ist eine innige Liebe geworden, die sich als Patina auf die Ehe gelegt hat."
    ],
  [
    "period" => 8,
    "name" => "Die Blecherne Hochzeit",
    "text" => "Nach acht Jahren ist in vielen Ehen der Alltag eingezogen. Das ist keineswegs etwas Negatives, auch wenn es im ersten Moment so klingt. Man versteht sich auch ohne Sprache, weiß, wie man miteinander umgehen muss, was man geben und was man nehmen kann und aus dem Ehepaar ist ein eingespieltes Team geworden."
    ],
  [
    "period" => 10,
    "name" => "Die Rosenhochzeit",
    "text" => "Ein ganzes Jahrzehnt verheiratet, damit ist die Rosenhochzeit einer der wichtigen Hochzeitstage. Seite an Seite mit einem anderen Menschen. Da erlebt man viel Gutes und muss auch mal schlechte Tage teilen. Da ist es Zeit sich zu zeigen, dass man sich liebt.\nUnd wie geht das besser und romantischer als mit der Blume der Liebe, der Rose?\nBlüte und Dornen symbolisieren von der Liebe berührte Momente. Die duftende Blüte zeigt Reife und Schönheit, ihr Stiel mit den Dornen symbolisiert Zeiten in denen man auf Konflikte und belastete Zeiten zurückschauen muss."
    ],
  [
    "period" => 11,
    "name" => "Die Stahlhochzeit",
    "text" => "Elf Jahre verheiratet, da halten Mann und Frau im Volksmund so fest zusammen wie Kruppstahl. Der starke Zusammenhalt des Paares wird auch in den weiteren Ehejahren den Hochs und Tiefs standhalten. Stahl wird oft auch als Grundgerüst beim Hausbau verwendet.\nUnd genauso spiegelt die Stahlhochzeit die Standfestigkeit und Stabilität der Ehe wider, die ihrerseits auch auf guten Grund gebaut ist."
    ],
  [
    "period" => 12,
    "month" => 6,
    "name" => "Die Petersilienhochzeit",
    "text" => "Dieses Datum ist für viele Ehepaare etwas Besonderes. Da die Petersilienhochzeit die Halbzeit zur Silberhochzeit markiert, wird sie von vielen Paaren gerne gefeiert. Die Petersilie steht im übertragenden Sinne für das Gedeihen der Ehe in den kommenden Jahren, sie soll schmackhaft und grün bleiben."
    ],
  [
    "period" => 13,
    "name" => "Veilchenhochzeit",
    "text" => "Der 13. Hochzeitstag ist auch unter den Namen Maiglöckchen Hochzeit und Spitzenhochzeit bekannt. Wie auch immer man ihn bezeichnet, all die Namensgeber haben eines gemeinsam:\nSie zeigen, dass die Ehe verletzlich ist wie eine Pflanze oder so empfindlich wie feine Spitze. Sie muss gepflegt werden."
    ],
  [
    "period" => 14,
    "name" => "Elfenbeinhochzeit",
    "text" => "Elfenbein ist ein kostbares und rares Gut. Auch viele Ehen halten den Irrungen und Wirrungen der Zeit nicht Stand. Paare die diesen Tag erreicht haben, sollten ihre Ehe weiterhin pflegen wie das kostbare Elfenbein. Zwar ist das Elfenbein ein Symbol für Härte und Unzerstörbarkeit, es muss aber, ebenso wie eine gute Ehe, stets gepflegt werden."
    ],
  [
    "period" => 15,
    "name" => "Die Gläserne Hochzeit",
    "text" => "Dieser Tag steht nicht etwas für Zerbrechlichkeit, im Gegenteil. Die Gläserne Hochzeit zeigt, dass die Eheleute fest miteinander verbunden sind. Man weiß, was der andere denkt und führt."
    ],
  [
    "period" => 20,
    "name" => "Porzellan Hochzeit",
    "text" => "In 20 Jahren Ehe kann im Streit auch mal der ein oder andere Teller aus Porzellan Sprünge bekommen oder sogar zu Bruch gehen. Daher wird dieses Jubiläum in manchen Regionen auch die Dornenhochzeit genannt.\nIm Alltag fällt in jeder Beziehung mal ein Wort, das einen kleinen Riss oder Stich hinterlassen kann. Wie jeder aber weiß sind Porzellan und Dornen so stabil, dass sie nicht zerbrechen. Ebenso hält die Ehe nach 20 Jahren viel aus und bleibt fest und stabil."
    ],
  [
    "period" => 25,
    "name" => "Die Silberhochzeit",
    "text" => "Eines der wohl wichtigsten Hochzeitstage überhaupt ist die Silberhochzeit. Die Ehe dauert nun schon ein viertel Jahrhundert an. Wie altes Silber hat sie ihren bleibenden Wert unter Beweis gestellt. Viele Eheleute feiern diesen Tag gebührend mit Verwandten, Bekannten und Freunden, die sie in ihrer bisher 25-jährigen Ehe begleitet haben."
    ],
  [
    "period" => 30,
    "name" => "Die Perlenhochzeit",
    "text" => "Nach 30 Jahren Ehe feiert man die Perlenhochzeit. Die aneinanderreihenden Perlen einer Kette stehen symbolisch für die aneinanderreihenden Tage der Ehe. Jede Perle, jeder Tag, hat eine eigene Geschichte, so wurden Kinder geboren, vielleicht ein Haus gebaut, das Paar hatte gute und schlechte Zeiten."
    ],
  [
    "period" => 35,
    "name" => "Die Leinen Hochzeit",
    "text" => "Nach 35 Jahren hat die Ehe gezeigt hat, das sie so unzerreißbar ist wie gutes Leinen, aber auch flexibel genug um nicht immer nur starren Regeln zu folgen Das traditionelle Geschenk zu diesem Hochzeitstag ist Wäsche."
    ],
  [
    "period" => 40,
    "name" => "Die Rubin Hochzeit",
    "text" => "Der Edelstein Rubin, als Namensgeber, wird als Stein des Lebens und der Liebe bezeichnet. Man sagt ihm nach, dass er die Kräfte aller anderen Edelsteine vereint.\nRot steht dabei für das Feuer der Liebe, das auch nach 40 Ehejahren noch immer leuchtet. Traditionell wird am Tag der Rubinhochzeit der Ehering der Frau mit einem roten Rubin veredelt."
    ],
  [
    "period" => 45,
    "name" => "Die Messinghochzeit",
    "text" => "ie Bedeutung dieses Tages leitet sich von den Eigenschaften des Metalls ab. Messing ist schwer, extrem haltbar, aber dennoch dehnbar.\nGenauso verhält es sich auch mit der Ehe nach 45 Jahren. Sie wiegt schwer und ist doch noch flexibel. Und nach 45 Jahren weit sie auch eine gewisse Haltbarkeit auf, viele Paar werden sich jetzt nicht mehr trennen, egal was jetzt noch kommen mag."
    ],
  [
    "period" => 50,
    "name" => "Die Goldene Hochzeit",
    "text" => "Wow, 50 Jahre verheiratet, ein halbes Jahrhundert Ehemann und Ehefrau. Was liegt da näher als dieses Jubiläum mit einem der edelsten Metalle der Welt zu feiern. Viele Paare erneuern nach 50 Jahren ihr Ehegelöbnis in der Kirche und feiern gemeinsam mit Verwandten, Bekannten und Freunden.\nDa sich die meisten Jubilare bei ihrer Goldenen Hochzeit schon in gehobenen Alter befinden, wird das Fest meist von den Kindern und Enkeln ausgerichtet. Die Jubilare dürfen sich dabei ihre Träume, die bei Ihrer Hochzeitsfeier zu kurz kamen, erfüllen. Damit ist die Goldene Hochzeit einer der wichtigsten Hochzeitstage. Ein wundervolles Geschenk ist ein Zweitring zur Ehe."
    ],
  [
    "period" => 55,
    "name" => "Die Juwelenhochzeit",
    "text" => "Am 55. Hochzeitstag wird die Juwelenhochzeit gefeiert. Als Juwelen werden geschliffene Edelsteine bezeichnet. Auch die Ehe hat sich im Laufe der Jahre abgeschliffen. Ecken und Kanten sind poliert. Jetzt zeigt die Ehe, wie die Steine, ihre Kraft und Reinheit. Ein Juwel ist etwas wertvolles. Er ist wertbeständig und nahezu unzerstörbar. Ebenso wie die Ehe, die mehr als ein halbes Jahrhundert überstanden hat."
  ],
  [
    "period" => 60,
    "name" => "Die Diamanthochzeit",
    "text" => "Die Diamantene Hochzeit ist ein ganz besonderes und außergewöhnliches Jubiläum. Diamantene Hochzeit, das bedeutet 60 Jahre Ehe. 60 Jahre, in denen Kinder, Enkelkinder und Urenkelkinder geboren und Höhen und Tiefen bewältigt wurden. Bedingungslose Liebe, Treue und Zusammenhalt sind die Faktoren, die eine solch lange Ehe erst ermöglichen."
    ],
  [
    "period" => 65,
    "name" => "Die Eiserne Hochzeit",
    "text" => "Genau wie das Eisen hält die Ehe nach 65 Jaher zahlreichen Angriffen stand, ohne an Substanz zu verlieren. Das Ehepaar hat gute und schlechte Zeiten durchstanden, den Kampf gegen Krankheiten aufgenommen und Bewährungsproben überstanden."
    ],
  [
    "period" => 70,
    "name" => "Die Gnadenhochzeit",
    "text" => "Warum sich dieser Hochzeitstag „Gnadenhochzeit“ nennt, ist nicht überliefert. Auf jeden Fall ist es einer der ganz besonderen Hochzeitstage. Vielleicht, weil nach so langer Zeit nicht nur die Ehe in die Jahre gekommen ist, sondern auch das Ehepaar? Der Begriff Gnade wird fast ausschließlich mit dem Christentum und der damit verbundenen Gottesgnade in Verbindung gebracht und bedeutet hier \"wohlwollend\"."
    ],


];

$longest_name = 0;
$longest_text = 0;

foreach ($past_dates as $index_past_date => $past_date) {
    foreach ($periods as $index_period => $info) {
        $longest_name = max(strlen($info["name"]), $longest_name);
        $longest_text = max(strlen($info["text"]), $longest_text);
    }
}


?>
struct hochzeitstag {
  int period; char name[<?= $longest_name + 1 ?>]; char text[<?= $longest_text + 1 ?>];
};

<?php
foreach (array_keys($past_dates) as $key => $name) {
  print "#define ".strtoupper($name)." ${key}\n";
}
print "const char *dates[".sizeof($past_dates)."][".sizeof($periods)."];\n";

foreach ($past_dates as $index_past_date => $past_date) {
    $date = new DateTime($past_date);
    foreach ($periods as $index_period => $info) {
        $day = clone $date;
        $day->add(new DateInterval("P".$info["period"]."Y".(isset($info["month"]) ? $info["month"]."M" : "")));
//        print "dates[".strtoupper($index_past_date)."][".$index_period."] = ".$day->format("U")."\n";
        // print "hochzeitstage[".strtoupper($index_past_date)."][".$index_period."] =
//    $date->format("c U")."   ".$day->format("c")."\n";
    }
}

print "struct hochzeitstag hochzeitstage[".sizeof($periods)."] = {\n";


foreach ($periods as $index_period => $info) {
  // print "hochzeitstage[".$index_period."].period  = ".$info["period"].";\n";
  // print "hochzeitstage[".$index_period."].name  = \"".$info["name"]."\";\n";
  // print "hochzeitstage[".$index_period."].text  = \"".preg_replace("/\n/m", '\n', $info["text"])."\";\n";
  print "  {".$info["period"].", \"".convert($info["name"])."\", \"".preg_replace("/\n/m", '\n', convert($info["text"]))."\"},\n";
}
print "};\n";
