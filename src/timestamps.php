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
    "text" => "Wie jeder weiß, ist Papier nicht besonders stabil. So gilt auch die Partnerschaft nach einem Ehejahr noch lange nicht als gefestigt. Sie ist hauchdünn, wie Papier und kann leicht zerreißen. Dennoch haben die Eheleute das erste Ehejahr erfolgreich gemeistert. Das heißt natürlich nicht, dass es immer ein reines Honigschlecken war. Sicherlich musste das junge Paar schon so manche Klippe umschiffen. Daher sollten Sie auch das erste Ehejubiläum nicht ohne Worte unter den Tisch kehren."
    ],
  [
    "period" => 2,
    "name" => "Die Baumwollenhochzeit",
    "text" => "Obwohl die Baumwolle ein recht robuster Stoff ist, der sich bei sehr hohen Temperaturen waschen lässt, wird sie mit jeder Reinigung etwas dünner. Um diesen Vergleich nun auf die Baumwollene Hochzeit anzuwenden, heißt das: Die Ehe ist nach zwei gemeinsam verbrachten Jahren sicherlich schon relativ fest. Sie gerät auch durch stärkere Erschütterungen nicht aus den Fugen."
    ],
  [
    "period" => 3,
    "name" => "Die Lederne Hochzeit",
    "text" => "Nach drei Jahren Ehe ist die Beziehung nicht mehr so dünn, wie Papier. Sie wird nicht bei jedem kleinen Problem auf die Zerreißprobe gestellt, sondern ist mittlerweile so zäh, wie Leder. Allerdings sollten sich die Ehepartner bewusst sein, dass auch eine gefestigte Beziehung gepflegt werden will. Denn, ebenso wie Leder spröde wird, wenn Sie es vernachlässigen, leidet auch die Ehe, wenn sie nur noch vor sich hinplätschert."
    ],
  [
    "period" => 4,
    "name" => "Die Seiden Hochzeit",
    "text" => "Die Seide gilt als die stärkste Naturfaser überhaupt. Daraus lässt sich schließen, dass nun, nach vier Jahren des Zusammenlebens auch die Ehe eine gewisse Stärke erreicht hat. Außerdem ist die Seide edel und kostbar. Und genau diese Eigenschaften treffen auch auf eine vierjährige, glückliche Ehe zu. Schließlich ist es heutzutage längst keine Selbstverständlichkeit, dass eine Ehe länger als drei Jahre hält."
    ],
  [
    "period" => 5,
    "name" => "Die Hölzerne Hochzeit",
    "text" => "Wenn ein Ehepaar 5 Jahre verheiratet ist, dann hat die Ehe Bestand. Sie ist so fest wie Holz und wird deshalb auch als Hölzerne Hochzeit bezeichnet. Um dem Jubelpaar eine weiterhin glückliche und harmonische Ehe zu wünschen, wird auf Holz geklopft."
    ],
  [
    "period" => 6,
    "name" => "Die Zinn Hochzeit",
    "text" => "Wie Zinn sollte auch die Ehe von Zeit zu Zeit ein bisschen aufgeputzt und poliert werden. Das verleiht neuen Glanz und neuen Schwung. Weil Zinn sehr weich und formbar ist, steht es sinnbildlich für die Formbarkeit der Ehe. Nutzt diesen Tag und probiert etwas Neues aus."
    ],
  [
    "period" => 7,
    "name" => "Die Kupferne Hochzeit",
    "text" => "Kupfer ist ein leicht formbares Metall, das nach einigen Jahren Patina ansetzt. Ebenso gilt auch die Ehe nach sieben Jahren noch als leicht formbar. Kein Ehepaar sollte sich jetzt auf seinen Lorbeeren ausruhen. Wenn die Zärtlichkeiten weniger werden und die Streitigkeiten zunehmen, ist das der Anfang vom Ende. Dass eine Ehe in jedem Jahr in die Brüche gehen kann, darüber sollten sich alle Eheleute bewusst sein."
    ],
  [
    "period" => 8,
    "name" => "Die Blecherne Hochzeit",
    "text" => "Als Blech wird in der Regel ein dünn gewalztes Metall bezeichnet. Um welche Art von Metall es sich dabei handelt ist nicht bestimmt. Aber durch die Dicke ist festgelegt, dass es sich um ein biegbares Metallstück handelt. Die Bezeichnung Blecherne Hochzeit heißt also, dass die Ehe des Jubelpaares zwar beständig ist, sich aber durchaus noch formen lässt. Nach acht Ehejahren haben sich die beiden Partner aneinander gewöhnt."
    ],
  [
      "period" => 9,
      "name" => "Die Keramikhochzeit",
      "text" => "Als Keramik werden in der Regel gebrannte Gebrauchs- oder Ziergegenstände bezeichnet. Das heißt, es handelt sich um Produkte, die sich im Rohzustand leicht verformen lassen, aber nach einer gewissen Zeit im Ofen hart und stabil sind. Sicherlich orientiert sich der Name Keramikhochzeit an diesen Eigenschaften des Materials. Denn nach 9 Ehejahren hat die Ehe bereits feste Formen angenommen. Die Gewohnheiten des Partners sind ebenso bekannt, wie seine kleinen Makel."
      ],
  [
    "period" => 10,
    "name" => "Die Rosenhochzeit",
    "text" => "Bei vielen Menschen gilt die Rose als die Königin der Blumen, denn sie ist wunderschön. Gleichzeitig ist sie die Blume der Liebe, weshalb ihr auch das erste Zehnerjubiläum der Hochzeitstage gewidmet sein darf. Denn wer seinen 10. Hochzeitstag begeht, liebt sich wirklich. Längst wurde die rosarote Brille abgelegt. Der Partner wird so gesehen, geliebt und respektiert, wie er ist."
    ],
  [
    "period" => 11,
    "name" => "Die Stahlhochzeit",
    "text" => "Hart wie Stahl ist die Bedeutung, die der Ehe nach 11 gemeinsamen Jahren zugeschrieben wird. Sicherlich ist das nicht verkehrt, denn wer elf Ehejahre hinter sich hat, der hat gemeinsam mit seinem Partner schon so manche Höhen und Tiefen durchlebt. Dass die Ehe immer noch Bestand hat, ist ein deutliches Zeichen für ihre Härte."
    ],
  [
    "period" => 12,
    "name" => "Die Nickelhochzeit",
    "text" => "Nickel ist ein Metall, das wegen seiner hohen Widerstandsfähigkeit gegenüber Luft, Wasser, Säuren und Laugen gerne in viel benutzten Gegenständen zusammen mit anderen Metallen verarbeitet wird. Es gilt als sehr beständig und so bedeutet die Nickelhochzeit, dass auch die Ehe nach 12 Jahren eine gewisse Beständigkeit hat. Das Ehepaar kennt sich nach so vielen Jahren in- und auswendig und hat es gelernt, auch den Alltag zu meistern."
    ],
  [
    "period" => 13,
    "name" => "Veilchenhochzeit",
    "text" => "Obwohl die meisten Menschen wahrscheinlich wissen, wie ein Veilchen aussieht, haben sie in freier Natur noch keines zu sehen bekommen. Das liegt daran, dass die kleine, blaue Blume, die wir uns so gern im Blumentopf aufs Fensterbrett stellen, eher im Verborgenen blüht. Sie ist unter Büschen oder am Waldrand zu finden. Und weil das Veilchen trotz seiner Schönheit recht unscheinbar und schlicht ist, steht es sogar in Gedichten als Symbol für Bescheidenheit."
    ],
  [
    "period" => 14,
    "name" => "Elfenbeinhochzeit",
    "text" => "Elfenbein wird aus den Stoßzähnen von Nilpferden und Elefanten gewonnen. Damit diese zentnerschweren Tiere sich mit ihren Zähnen bekämpfen und verletzen können, muss das Material sehr hart sein. Wahrscheinlich ist die Bedeutung der Elfenbeinhochzeit genau diesem Umstand zu verdanken. Denn auch eine Ehe, die in 14 Jahren sicher nicht immer nur Zuckerschlecken war, muss sehr hart im Sinne von stark sein, um so lange zu bestehen."
    ],
  [
    "period" => 15,
    "name" => "Die Gläserne Hochzeit",
    "text" => "Nach einem lustigen Brauch wird zur Kristallhochzeit der Garten des Paares mit Girlanden aus Glasflaschen geschmückt. Der Hof vor dem Haus oder der Weg zur Haustüre wird ebenfalls gerne mit Flaschen vollgestellt. Wegen dieser Bräuche nennt sich in manchen Gegenden der 15. Hochzeitstag Flaschenhochzeit. Welcher Name auch verwendet wird, eines ist allen gemeinsam: das durchsichtige, zerbrechliche Glas."
    ],
  [
    "period" => 16,
    "name" => "Die Saphirhochzeit",
    "text" => "Allgemeine Bräuche zur Saphirhochzeit gibt es nicht. Weil der 16. Hochzeitstag den Namen eines Edelsteines trägt, ist es in manchen Kreisen üblich, der Ehefrau ein Schmuckstück mit einem blauen Saphir zu schenken. Das ist aber kein Muss, denn schließlich zählt der blaue Saphir zu den teuersten Schmucksteinen und nicht jedermann hat einen wohlgefüllten Geldbeutel. Sicher lässt sich der Hochzeitstag auch ohne ein so teures Geschenk gebührend feiern."
  ],
  [
    "period" => 17,
    "name" => "Die Orchideenhochzeit",
    "text" => "Die Orchidee gilt nicht nur als eine sehr wertvolle Blüte, sondern auch als eine Pflanze, die schwer zu pflegen ist. Deswegen hat der Name Orchideenhochzeit wohl zweierlei Bedeutung. Einerseits weist er darauf hin, dass eine Ehe, die 17 Jahre lang gut gegangen ist, als wertvoll betrachtet werden darf. Andererseits macht er darauf aufmerksam, dass es nicht so einfach ist, den 17. Hochzeitstag zu erreichen. Denn nur wer seine Liebe pflegt kann die Orchideenhochzeit feiern." 
  ],
  [
    "period" => 18,
    "name" => "Die Türkishochzeit",
    "text" => "Ebenso, wie der Türkis ein wertvolles Mineral ist, darf auch der 18. Hochzeitstag als selten und wertvoll angesehen werden. Schließlich gibt es nicht viele Ehepaare, die diesen Hochzeitstag miteinander verbringen dürfen. Besondere Bräuche gibt es für die Türkishochzeit nicht. Ein Geschenk, von Verwandten oder Freunden, das zeigt, dass sie an das Jubelpaar denken, wird aber gerne angenommen."
  ],
  [
    "period" => 19,
    "name" => "Die Perlmutthochzeit",
    "text" => "Ebenso wie das harte Perlmutt einige Jahre braucht, um seine Widerstandsfähigkeit zu erreichen, hat auch die 19 jährige Ehe einige Zeit benötigt, um ihre jetzige Stabilität zu erreichen. Nach fast einem fünftel Jahrhundert ist die Partnerschaft so fest wie Perlmutt. Die Eheleute verstehen sich ohne Worte und wissen genau, um die Freuden und Leiden des Partners bescheid."
  ],
  [
    "period" => 20,
    "name" => "Die Porzellan Hochzeit",
    "text" => "Weil gutes Porzellan teuer und edel ist, wurde es schon früher als \"das Gold in Weiß\" bezeichnet. Und genau aus diesen Eigenschaften heraus lässt sich auch der Name für das 20. Hochzeitsjubiläum ableiten. Denn schließlich darf eine Ehe, in der sich die Partner bereits seit 20 Jahren treu zur Seite stehen, ebenfalls als teuer und kostbar angesehen werden. Nicht viele Paare erreichen dieses Hochzeitsjubiläum."
  ],
  [
    "period" => 21,
    "name" => "Die Opal Hochzeit",
    "text" => "Dass eine Ehe länger als 20 Jahre hält, ist keine Selbstverständlichkeit. Im Gegenteil, eine so lange andauernde Beziehung muss als etwas besonders Wertvolles und Außergewöhnliches betrachtet werden. Sie ist sicherlich ebenso kostbar, wie ein Opal. Althergebrachte Bräuche gibt es zu diesem Jubiläum nicht und auch beim Schmücken des Festtisches und des Festraumes kann man seiner Fantasie freien Lauf lassen."
  ],
  [
    "period" => 22,
    "name" => "Die Bronze Hochzeit",
    "text" => "Aus Bronze werden beispielsweise Wandteller gefertigt, die mit einer hübschen Widmung versehen werden können. Aber auch kleine Bronzeskulpturen für die Vitrine oder die Fensterbank eignen sich als Mitbringsel zum 22. Hochzeitstag. Wer sein Geschenk mit einer lustigen Rede an den Mann und die Frau bringen möchte, verschenkt eine Bronzemedaille und macht eine Anspielung auf die zu erwartende Silberhochzeit und die ebenfalls noch bevorstehende Goldene Hochzeit."
  ],
  [
    "period" => 23,
    "name" => "Die Titan Hochzeit",
    "text" => "Ob sich der Name Titanhochzeit für den 23. Hochzeitstag von dem gleichnamigen Metall ableiten lässt, oder ob es eher auf das Göttergeschlecht aus der griechischen Mythologie zurückzuführen ist, lässt sich heute nicht mehr klären. Da die Ehe nach 23 Jahren einen beinahe göttlichen Status erreicht hat, und somit ebenso beständig ist, wie Titan, klingen beide Erklärungen einleuchtend."
  ],
  [
    "period" => 24,
    "name" => "Die Satin Hochzeit",
    "text" => "Wie der 24. Hochzeitstag zu der Bezeichnung Satinhochzeit kam, lässt sich heute nicht mehr ganz nachvollziehen. Vielleicht lässt sich mit der Festigkeit des Gewebes ein Bezug zur Festigkeit der Ehe schaffen, die nach 24 Jahren sicherlich schon einige Zerreißproben überstehen musste. Vielleicht gibt der Name aber auch einen Hinweis auf die besondere Pflege, die sowohl der empfindliche Satinstoff verlangt, wie auch eine Ehe, die nach so langer Zeit noch immer glücklich und beständig ist."
  ],
  [
    "period" => 25,
    "name" => "Die Silberhochzeit",
    "text" => "Eines der wohl wichtigsten Hochzeitstage überhaupt ist die Silberhochzeit. Die Ehe dauert nun schon ein viertel Jahrhundert an. Wie altes Silber hat sie ihren bleibenden Wert unter Beweis gestellt. Viele Eheleute feiern diesen Tag gebührend mit Verwandten, Bekannten und Freunden, die sie in ihrer bisher 25-jährigen Ehe begleitet haben."
    ],
  [
    "period" => 30,
    "name" => "Die Perlenhochzeit",
    "text" => "Die Perlen, die auf der Perlenkette aneinandergereiht sind, stehen symbolisch für die vielen sich aneinanderreihenden Tage der Ehe. Jede Perle soll an ein Erlebnis der gemeinsam verbrachten 30 Ehejahre erinnern. Die Bedeutung der sich aneinanderreihenden Perlen weist also einerseits auf die Länge hin, die die Beziehung nun bereits überstanden hat. Und sie zeigt gleichzeitig, dass es sich um eine sehr wertvolle Partnerschaft handelt. So wertvoll wie Perlen."
    ],
  [
    "period" => 35,
    "name" => "Die Leinen Hochzeit",
    "text" => "Die Bezeichnung Leinwandhochzeit stammt aus früheren Zeiten. Er ist entstanden, als es die Fotografie noch nicht gab. Damals ließen sich die Jubelpaare als Andenken an ihren 35. Hochzeitstag auf Leinwand malen. Sie wurde gewählt, weil sie aus Leinen bestand und es ein fester und extrem reißfester Stoff ist. Trotz seiner Robustheit ist Leinen flexibel und lässt sich daher mit seinen typischen Eigenschaften hervorragend als Symbol für eine so lange bestehende Lebensgemeinschaft verwenden." 
    ],
  [
    "period" => 40,
    "name" => "Die Rubin Hochzeit",
    "text" => "Der Edelstein Rubin, als Namensgeber, wird als Stein des Lebens und der Liebe bezeichnet. Man sagt ihm nach, dass er die Kräfte aller anderen Edelsteine vereint. Rot steht dabei für das Feuer der Liebe, das auch nach 40 Ehejahren noch immer leuchtet. Traditionell wird am Tag der Rubinhochzeit der Ehering der Frau mit einem roten Rubin veredelt."
    ],
  [
    "period" => 45,
    "name" => "Die Messinghochzeit",
    "text" => "Die Bedeutung dieses Tages leitet sich von den Eigenschaften des Metalls ab. Messing ist schwer, extrem haltbar, aber dennoch dehnbar. Genauso verhält es sich auch mit der Ehe nach 45 Jahren. Sie wiegt schwer und ist doch noch flexibel. Und nach 45 Jahren weit sie auch eine gewisse Haltbarkeit auf, viele Paar werden sich jetzt nicht mehr trennen, egal was jetzt noch kommen mag."
    ],
  [
    "period" => 50,
    "name" => "Die Goldene Hochzeit",
    "text" => "Wow, 50 Jahre verheiratet, ein halbes Jahrhundert Ehemann und Ehefrau. Was liegt da näher als dieses Jubiläum mit einem der edelsten Metalle der Welt zu feiern. Viele Paare erneuern nach 50 Jahren ihr Ehegelöbnis in der Kirche und feiern gemeinsam mit Verwandten, Bekannten und Freunden. Da sich die meisten Jubilare bei ihrer Goldenen Hochzeit schon in gehobenen Alter befinden, wird das Fest meist von den Kindern und Enkeln ausgerichtet."
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
    "text" => "Warum sich dieser Hochzeitstag \"Gnadenhochzeit\" nennt, ist nicht überliefert. Auf jeden Fall ist es einer der ganz besonderen Hochzeitstage. Vielleicht, weil nach so langer Zeit nicht nur die Ehe in die Jahre gekommen ist, sondern auch das Ehepaar? Der Begriff Gnade wird fast ausschließlich mit dem Christentum und der damit verbundenen Gottesgnade in Verbindung gebracht und bedeutet hier \"wohlwollend\"."
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
print "#define hochzeitstage_count ".sizeof($periods)."\n";
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
