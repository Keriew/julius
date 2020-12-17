#include "translation/common.h"
#include "translation/translation.h"

static translation_string all_strings[] = {
    {TR_NO_PATCH_TITLE, "Patch 1.0.1.0 ist nicht installiert"},
    {TR_NO_PATCH_MESSAGE,
        "Deine Caesar 3 Installation wurde noch nicht auf Version 1.0.1.0 aktualisiert. "
        "Der Patch kann hier heruntergeladen werden:\n"
        URL_PATCHES "\n"
        "Fortfahren auf eigene Gefahr."},
    {TR_MISSING_FONTS_TITLE, "Schriftarten fehlen"},
    {TR_MISSING_FONTS_MESSAGE,
        "Deine Caesar 3 Installation benötigt zusätzliche Schriftarten. "
        "Du kannst Schriftarten für deine Sprache hier herunterladen:\n"
        URL_PATCHES},
    {TR_NO_EDITOR_TITLE, "Editor nicht installiert"},
    {TR_NO_EDITOR_MESSAGE,
        "Deiner Caesar 3 Installation fehlen die Dateien für den Editor. "
        "Du kannst die fehlenden Dateien hier herunterladen:\n"
        URL_EDITOR},
    {TR_INVALID_LANGUAGE_TITLE, "Ungültiges Sprachverzeichnis"},
    {TR_INVALID_LANGUAGE_MESSAGE,
        "Das gewählte Verzeichnis enthält kein gültiges Sprachpaket. "
        "Bitte überprüfe das Protokoll auf Fehler."},
    {TR_BUTTON_OK, "OK"},
    {TR_BUTTON_CANCEL, "Abbrechen"},
    {TR_BUTTON_RESET_DEFAULTS, "Zurücksetzen"},
    {TR_BUTTON_CONFIGURE_HOTKEYS, "Tastenkombinationen"},
    {TR_BUTTON_NEXT, ">"},
    {TR_BUTTON_PREV, "<"},
    {TR_CONFIG_TITLE, "Augustus Einstellungen"},
    {TR_CONFIG_LANGUAGE_LABEL, "Sprache:"},
    {TR_CONFIG_LANGUAGE_DEFAULT, "(Standard)"},
    {TR_CONFIG_PAGE_LABEL, "Seite"},
    {TR_CONFIG_HEADER_UI_CHANGES, "Benutzeroberfläche ändern"},
    {TR_CONFIG_HEADER_GAMEPLAY_CHANGES, "Spielablauf ändern"},
    {TR_CONFIG_SHOW_INTRO_VIDEO, "Intro-Videos abspielen"},
    {TR_CONFIG_SIDEBAR_INFO, "Zusätzliche Informationen am rechten Bildschirmrand anzeigen"},
    {TR_CONFIG_SMOOTH_SCROLLING, "Aktiviere sanftes Scrollen"},
    {TR_CONFIG_DISABLE_RIGHT_CLICK_MAP_DRAG, "Rechtsklick deaktivieren, um die Karte zu verschieben"},
    {TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE, "Das visuelle Feedback beim Planieren verbessern"},
    {TR_CONFIG_ALLOW_CYCLING_TEMPLES, "Erlaube alle Tempel nacheinander zu bauen"},
    {TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE, "Zeige Reichweite beim Bauen von Reservoirs und Brunnen"},
    {TR_CONFIG_SHOW_CONSTRUCTION_SIZE, "Zeige Konstruktionsgröße beim Bauen"},
    {TR_CONFIG_HIGHLIGHT_LEGIONS, "Hebe Legion beim Berühren mit der Maus hervor"},
    {TR_CONFIG_ROTATE_MANUALLY, "Drehe Torhaus und Triumphbogen mit Tastenkombination"},
    {TR_CONFIG_SHOW_MILITARY_SIDEBAR, "Zeige Legionen am rechten Bildschirmrand"},
    {TR_CONFIG_DISABLE_RIGHT_CLICK_MAP_DRAG, "Verschieben der Karte mit der rechten Maustaste deaktivieren"},
    {TR_CONFIG_FIX_IMMIGRATION_BUG, "Behebe Immigrationsfehler auf 'Sehr schwierig'"},
    {TR_CONFIG_FIX_100_YEAR_GHOSTS, "Behebe '100 Jahre alte Geister'"},
    {TR_CONFIG_FIX_EDITOR_EVENTS, "Behebe Wechsel- und Überlebenszeit des Imperators in eigenen Missionen"},
    {TR_CONFIG_DRAW_WALKER_WAYPOINTS, "Setze Fußgängerwegpunkte durch Rechtsklicken der Zielgebäude"},
    {TR_CONFIG_ENABLE_ZOOM, "Aktiviere Zoom (langsamer, benötigt mehr RAM)"},
    {TR_CONFIG_COMPLETE_RATING_COLUMNS, "Behebe unvollständige Bewertungsspalten bei geringen Zielen"},
    {TR_CONFIG_GRANDFESTIVAL, "Große Feste ermöglichen einen zusätzlichen Segen von einem Gott"},
    {TR_CONFIG_JEALOUS_GODS, "Deaktiviere Eifersucht der Götter"},
    {TR_CONFIG_GLOBAL_LABOUR, "Aktiviere globalen Arbeiterpool"},
    {TR_CONFIG_SCHOOL_WALKERS, "Vergrößere Laufreichweite von Schülern"},
    {TR_CONFIG_RETIRE_AT_60, "Erhöhe Rentenalter von 50 auf 60 Jahre"},
    {TR_CONFIG_FIXED_WORKERS, "Fester Arbeiterpool - 38% der Bevölkerung"},
    {TR_CONFIG_EXTRA_FORTS, "Ermögliche das Bauen 4 zusätzlicher Forts"},
    {TR_CONFIG_WOLVES_BLOCK, "Blockiere Gebäude in der Nähe von Wölfen"},
    {TR_CONFIG_DYNAMIC_GRANARIES, "Blockiere getrennte Straßen eines Silos"},
    {TR_CONFIG_MORE_STOCKPILE, "Häuser horten mehr Güter von Märkten"},
    {TR_CONFIG_NO_BUYER_DISTRIBUTION, "Der Kauf von Marktfrauen verteilt keine Güter"},
    {TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS, "Gebäude sofort zerstören"},
    {TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD, "Wagenschieber von sammelnden Silos können neben der Straße fahren"},
    {TR_CONFIG_GRANARIES_GET_DOUBLE, "Doppelte Kapazität für Wagenschieber sammelnder Silos"},
    {TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD, "Turmwächter brauchen keine Straßenverbindung zu einer Kaserne"},
    {TR_CONFIG_FARMS_DELIVER_CLOSE, "Farmen und Kais liefern nur an nahegelegene Silos"},
    {TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES, "Essen wird nicht an sammelnde Silos geliefert"},
    {TR_CONFIG_ALL_HOUSES_MERGE, "Alle Häuser verschmelzen"},
    {TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE, "Das öffnen einer Handelsroute, stellt eine andere Weinsorte bereit"},
    {TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY, "Zufällig einstürzende Lehmgruben und Eisenminen nehmen stattdessen Geld"},
    {TR_CONFIG_MULTIPLE_BARRACKS, "Erlaube das Errichten mehrerer Kasernen." },
    {TR_CONFIG_NOT_ACCEPTING_WAREHOUSES, "Warenhäuser nehmen nach dem Bau nichts an"},
    {TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS, "Häuser erweitern sich nicht in Gärten"},    
    {TR_HOTKEY_TITLE, "Augustus Tastenkombinationen einstellen"},
    {TR_HOTKEY_LABEL, "Tastenkombination"},
    {TR_HOTKEY_ALTERNATIVE_LABEL, "Alternativ"},
    {TR_HOTKEY_HEADER_ARROWS, "Pfeiltasten"},
    {TR_HOTKEY_HEADER_GLOBAL, "Globale Tastenkombinationen"},
    {TR_HOTKEY_HEADER_CITY, "Stadt"},
    {TR_HOTKEY_HEADER_ADVISORS, "Berater"},
    {TR_HOTKEY_HEADER_OVERLAYS, "Spezialkarten"},
    {TR_HOTKEY_HEADER_BOOKMARKS, "Lesezeichen für Stadtkarten"},
    {TR_HOTKEY_HEADER_EDITOR, "Editor"},
    {TR_HOTKEY_HEADER_BUILD, "Bau Tastenkombinationen"},
    {TR_HOTKEY_ARROW_UP, "Hoch"},
    {TR_HOTKEY_ARROW_DOWN, "Runter"},
    {TR_HOTKEY_ARROW_LEFT, "Links"},
    {TR_HOTKEY_ARROW_RIGHT, "Rechts"},
    {TR_HOTKEY_TOGGLE_FULLSCREEN, "Vollbild ein-/ausschalten"},
    {TR_HOTKEY_CENTER_WINDOW, "Fenster zentrieren"},
    {TR_HOTKEY_RESIZE_TO_640, "Fenstergröße: 640x480"},
    {TR_HOTKEY_RESIZE_TO_800, "Fenstergröße: 800x600"},
    {TR_HOTKEY_RESIZE_TO_1024, "Fenstergröße: 1024x768"},
    {TR_HOTKEY_SAVE_SCREENSHOT, "Screenshot speichern"},
    {TR_HOTKEY_SAVE_CITY_SCREENSHOT, "Stadtweiten Screenshot sp."},
    {TR_HOTKEY_BUILD_CLONE, "Gebäude unter Mauszeiger vervielfältigen"},
    {TR_HOTKEY_LOAD_FILE, "Datei laden"},
    {TR_HOTKEY_SAVE_FILE, "Datei speichern"},
    {TR_HOTKEY_INCREASE_GAME_SPEED, "Spielgeschwindigkeit erhöhen"},
    {TR_HOTKEY_DECREASE_GAME_SPEED, "Spielgeschwindigkeit reduzieren"},
    {TR_HOTKEY_TOGGLE_PAUSE, "Spiel pausieren"},
    {TR_HOTKEY_CYCLE_LEGION, "Durch Legionen wechseln"},
    {TR_HOTKEY_ROTATE_MAP_LEFT, "Karte nach links drehen"},
    {TR_HOTKEY_ROTATE_MAP_RIGHT, "Karte nach rechts drehen"},
    {TR_HOTKEY_SHOW_ADVISOR_LABOR, "Arbeitsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_MILITARY, "Militärberater"},
    {TR_HOTKEY_SHOW_ADVISOR_IMPERIAL, "Imperiumsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_RATINGS, "Wertungsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_TRADE, "Handelsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_POPULATION, "Bevölkerungsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_HEALTH, "Gesundheitsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_EDUCATION, "Bildungsbearter"},
    {TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT, "Unterhaltungsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_RELIGION, "Religionsberater"},
    {TR_HOTKEY_SHOW_ADVISOR_FINANCIAL, "Finanzberater"},
    {TR_HOTKEY_SHOW_ADVISOR_CHIEF, "Hauptberater"},
    {TR_HOTKEY_SHOW_ADVISOR_HOUSING, "Wohnraumberater"},
    {TR_HOTKEY_TOGGLE_OVERLAY, "Akt. Spezialkarte umschalten"},
    {TR_HOTKEY_SHOW_OVERLAY_WATER, "Wasserkarte"},
    {TR_HOTKEY_SHOW_OVERLAY_FIRE, "Feuerkarte"},
    {TR_HOTKEY_SHOW_OVERLAY_DAMAGE, "Schadenskarte"},
    {TR_HOTKEY_SHOW_OVERLAY_CRIME, "Kriminalitätskarte"},
    {TR_HOTKEY_SHOW_OVERLAY_PROBLEMS, "Problemkarte"},
    {TR_HOTKEY_ROTATE_BUILDING, "Gebäude drehen"},
    {TR_HOTKEY_GO_TO_BOOKMARK_1, "Gehe zu Lesezeichen 1"},
    {TR_HOTKEY_GO_TO_BOOKMARK_2, "Gehe zu Lesezeichen 2"},
    {TR_HOTKEY_GO_TO_BOOKMARK_3, "Gehe zu Lesezeichen 3"},
    {TR_HOTKEY_GO_TO_BOOKMARK_4, "Gehe zu Lesezeichen 4"},
    {TR_HOTKEY_SET_BOOKMARK_1, "Setze Lesezeichen 1"},
    {TR_HOTKEY_SET_BOOKMARK_2, "Setze Lesezeichen 2"},
    {TR_HOTKEY_SET_BOOKMARK_3, "Setze Lesezeichen 3"},
    {TR_HOTKEY_SET_BOOKMARK_4, "Setze Lesezeichen 4"},
    {TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO, "Kampfinformationen ein-/ausblenden"},
    {TR_HOTKEY_EDIT_TITLE, "Drücke neue Tastenkombination"},
    {TR_BUILDING_ROADBLOCK, "Straßensperre"},
    {TR_BUILDING_ROADBLOCK_DESC, "Straßensperren verhindern das unkontrollierte Umherwandern von Einwohnern." },
    {TR_BUILDING_ENGINEER_GUILD, "Baumeistergilde" },
    {TR_BUILDING_ENGINEER_GUILD_DESC, "Die Baumeister arbeiten unermüdlich an der Konstruktion von Monumenten für den Ruhm und die Pracht Roms." },
    {TR_BUILDING_GRAND_TEMPLE_ADD_MODULE, "Tempel einen Beinamen geben" },
    {TR_BUILDING_GRAND_TEMPLE_CERES, "Ceres' Prachttempel" },
    {TR_BUILDING_GRAND_TEMPLE_NEPTUNE, "Neptuns Prachttempel" },
    {TR_BUILDING_GRAND_TEMPLE_MERCURY, "Merkurs Prachttempel" },
    {TR_BUILDING_GRAND_TEMPLE_MARS, "Mars' Prachttempel" },
    {TR_BUILDING_GRAND_TEMPLE_VENUS, "Venus' Prachttempel" },
    {TR_BUILDING_PANTHEON, "Pantheon" },
    {TR_BUILDING_GRAND_TEMPLE_CERES_DESC, "Prachttempel der Ceres" },
    {TR_BUILDING_GRAND_TEMPLE_NEPTUNE_DESC, "Prachttempel des Neptun" },
    {TR_BUILDING_GRAND_TEMPLE_MERCURY_DESC, "Prachttempel des Merkur" },
    {TR_BUILDING_GRAND_TEMPLE_MARS_DESC, "Prachttempel des Mars" },
    {TR_BUILDING_GRAND_TEMPLE_VENUS_DESC, "Prachttempel der Venus" },
    {TR_BUILDING_PANTHEON_DESC, "Pantheon" },
    {TR_BUILDING_GRAND_TEMPLE_CERES_BONUS_DESC, "Wagenschieber von Farmen bewegen sich 50% schneller" },
    {TR_BUILDING_GRAND_TEMPLE_NEPTUNE_BONUS_DESC, "Reichweite von Brunnen und Ziehbrunnen um +1 erhöht, von Reservoirs um +2. Benötigte Arbeitskräfte für alle Wasserdienste um 50% reduziert. Handelsschiffe bewegen sich 25% schneller." },
    {TR_BUILDING_GRAND_TEMPLE_MERCURY_BONUS_DESC, "Händler zur See und an Land haben 50% zusätzliche Kapazität. Händler an Land bewegen sich 25% schneller." },
    {TR_BUILDING_GRAND_TEMPLE_MARS_BONUS_DESC, "Gestattet den Bau von vier extra Forts und funktioniert als zusätzliche Barracke." },
    {TR_BUILDING_GRAND_TEMPLE_VENUS_BONUS_DESC, "Dekorationen und Tempel erstrahlen in neuem Glanz und steigern die Attraktivität. Häuser lagern mehr Waren und bleiben auch ohne Dienste und Waren länger bestehen." },
    {TR_BUILDING_PANTHEON_BONUS_DESC, "Priester des Pantheons bieten Zugang zu allen fünf Gottheiten. Reduziert die Kosten von Tempelarbeitern um 25% und hält kostenlos kleine jährliche Feste ab." },
    {TR_BUILDING_GRAND_TEMPLE_CERES_MODULE_1_DESC, "Priester reduzieren Nahrungsverbrauch um 20% in Häusern mit Zugang zu einem Tempel der Ceres." },
    {TR_BUILDING_GRAND_TEMPLE_NEPTUNE_MODULE_1_DESC, "Tempel des Neptun produzieren Wagenlenker für die Reitbahn." },
    {TR_BUILDING_GRAND_TEMPLE_MERCURY_MODULE_1_DESC, "Priester des Merkur reduzieren Tonwaren- und Möbelverbrauch um 20% in Häusern mit Zugang zu einem Tempel des Merkur." },
    {TR_BUILDING_GRAND_TEMPLE_MARS_MODULE_1_DESC, "Priester des Mars erzeugen einmal pro Monat Nahrung, wenn sie Häuser passieren und liefern diese an den Versorgungsposten, sobald eine gewisse Menge erreicht ist. Dies erfordert eine Straßenverbindung." },
    {TR_BUILDING_GRAND_TEMPLE_VENUS_MODULE_1_DESC, "Der Prachttempel produziert Wein im Verhältnis zur Bevölkerung mit Zugang zu Tempeln der Venus. Priester verteilen ihn an die Häuser." },
    {TR_BUILDING_GRAND_TEMPLE_CERES_MODULE_2_DESC, "Tempel der Ceres agieren als Märkte. Sie sammeln und verteilen ein lokal produziertes Nahrungsmittel und Öl." },
    {TR_BUILDING_GRAND_TEMPLE_NEPTUNE_MODULE_2_DESC, "Priester erhöhen das Limit an Bewohnern um 5% für Häuser mit Zugang zu Tempeln des Neptun. Der Prachttempel des Neptun dient als gefülltes Reservoir ohne Zugang zu Wasser zu benötigen." },
    {TR_BUILDING_GRAND_TEMPLE_MERCURY_MODULE_2_DESC, "Priester reduzieren Öl- und Weinkonsum um 20% in Häusern mit Zugang zu einem Tempel des Merkur." },
    {TR_BUILDING_GRAND_TEMPLE_MARS_MODULE_2_DESC, "Priester reduizieren Verbrauch aller Waren um 10% in Häusern mit Zugang zu einem Tempel des Mars." },
    {TR_BUILDING_GRAND_TEMPLE_VENUS_MODULE_2_DESC, "Priester bieten Unterhaltung und verschönern Häuser, dies steigert die Attraktivität der Nachbarschaft ohne weitere Dekorationen." },
    {TR_BUILDING_PANTHEON_MODULE_1_DESC, "Alle Tempel der Stadt senden Priester zum Pantheon. Diese Priester verbreiten dann Glauben und Segen ihrer Götter!" },
    {TR_BUILDING_PANTHEON_MODULE_2_DESC, "Häuser mit Zugang zum Pantheon können sich eine Stufe weiterentwickeln." },
    {TR_BUILDING_GRAND_TEMPLE_CERES_DESC_MODULE_1, "Templum Ceres Promitor" },
    {TR_BUILDING_GRAND_TEMPLE_CERES_DESC_MODULE_2, "Templum Ceres Reparator" },
    {TR_BUILDING_GRAND_TEMPLE_NEPTUNE_DESC_MODULE_1, "Templum Neptunus Equester" },
    {TR_BUILDING_GRAND_TEMPLE_NEPTUNE_DESC_MODULE_2, "Templum Neptunus Adiutor" },
    {TR_BUILDING_GRAND_TEMPLE_MERCURY_DESC_MODULE_1, "Templum Mercurius Fortunus" },
    {TR_BUILDING_GRAND_TEMPLE_MERCURY_DESC_MODULE_2, "Templum Mercurius Abundantia" },
    {TR_BUILDING_GRAND_TEMPLE_MARS_DESC_MODULE_1, "Templum Mars Ultor" },
    {TR_BUILDING_GRAND_TEMPLE_MARS_DESC_MODULE_2, "Templum Mars Quirinus" },
    {TR_BUILDING_GRAND_TEMPLE_VENUS_DESC_MODULE_1, "Templum Venus Verticordia" },
    {TR_BUILDING_GRAND_TEMPLE_VENUS_DESC_MODULE_2, "Templum Venus Genetrix" },
    {TR_BUILDING_PANTHEON_DESC_MODULE_1, "Pantheum Ara Maxima" },
    {TR_BUILDING_PANTHEON_DESC_MODULE_2, "Pantheum Roma Aeterna" },
    {TR_BUILDING_GRAND_TEMPLE_MENU, "Prachttempel" },
    {TR_BUILDING_WORK_CAMP, "Arbeiterlager" },
    {TR_BUILDING_WORK_CAMP_DESC, "Arbeiter versammeln sich hier, um Materialien an Baustellen zu liefern." },
    {TR_HEADER_HOUSING, "Wohnraum"},								
    {TR_ADVISOR_HOUSING_ROOM, "In der Stadt gibt es noch Platz für"},
    {TR_ADVISOR_HOUSING_NO_ROOM, "In der Stadt gibt es keinen Wohnraum mehr."},
    {TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY, "Die Bevölkerung verlangt nach Tonwaren"},
    {TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE, "Die Bevölkerung verlangt nach Möbeln"},
    {TR_ADVISOR_RESIDENCES_DEMANDING_OIL, "Die Bevölkerung verlangt nach Öl"},
    {TR_ADVISOR_RESIDENCES_DEMANDING_WINE, "Die Bevölkerung verlangt nach Wein"},
    {TR_ADVISOR_TOTAL_NUM_HOUSES, "Wohnhäuser gesammt:"},
    {TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY, "Verfügbare Kapazität:"},
    {TR_ADVISOR_TOTAL_HOUSING_CAPACITY, "Kapazität gesammt:"},
    {TR_ADVISOR_ADVISOR_HEADER_HOUSING, "Bevölkerung - Wohnraum"},
    {TR_ADVISOR_BUTTON_GRAPHS, "Diagramme"},
    {TR_ADVISOR_HOUSING_PROSPERITY_RATING, "Wohnungswohlstand beträgt"},
    {TR_ADVISOR_PERCENTAGE_IN_VILLAS_PALACES, "Die prozentuale Bevölkerungszahl in Villen und Palästen beträgt"},
    {TR_ADVISOR_PERCENTAGE_IN_TENTS_SHACKS, "Die prozentuale Bevölkerungszahl in Zelten und Baracken beträgt"},
    {TR_ADVISOR_AVERAGE_TAX, "Durchschnittliche Steuereinnahmen pro Wohnhaus betragen"},
    {TR_ADVISOR_AVERAGE_AGE, "Durchschnittliches Alter der Bevölkerung beträgt"},
    {TR_ADVISOR_PERCENT_IN_WORKFORCE, "Die prozentuale Bevölkerungszahl in der Arbeiterschaft beträgt"},
    {TR_ADVISOR_BIRTHS_LAST_YEAR, "Geburten im vergangen Jahr:"},
    {TR_ADVISOR_DEATHS_LAST_YEAR, "Tode im vergangen Jahr:"},
    {TR_ADVISOR_TOTAL_POPULATION, "Bewohner gesammt"}
    {TR_REQUIRED_RESOURCES, "Gelieferte Ressourcen für aktuelle Phase:"},
    {TR_BUILDING_GRAND_TEMPLE_CONSTRUCTION_DESC, "Der Bau eines Prachttempels benötigt in einem Lagerhaus gelagerte Waren, Arbeiter von einem Arbeiterlager und Baumeister von einer Baumeistergilde."},
    {TR_CONSTRUCTION_PHASE, "Konstruktionsphase:"},
    {TR_ADD_MODULE, "Tempel Beiname ändern?"},
    {TR_BUILDING_TEMPLE_MODULE_CONSTRUCTED, "Beiname zugewiesen."},
    {TR_BUILDING_CERES_TEMPLE_QUOTE, "Ceres teilte zuerst mit gebogenem Pfluge die Schollen,\nGab Feldfrüchte den Ländern zuerst\n und mildere Nahrung,\nOrdnete Sitten zuerst; ja, alles ist Gabe der Ceres.\nCeres gebührt mein Sang.\n-Ovid, die Metamorphose; Ceres und Proserpina" },
    { TR_BUILDING_NEPTUNE_TEMPLE_QUOTE, "Nicht bleibt zürnend die See. Hinlegend die zackige Waffe\nGlättet die Flut der Beherrscher des Meers,\nUnd den bläulichen Triton rufet er,\nDer an der Schulter bedeckt von haftenden Schnecken\nÜber der Tiefe sich hebt,\nund heißt in die tönende Muschel.\n-Ovid, die Metamorphose; Deukalion und Pyrrha"},
    {TR_BUILDING_MERCURY_TEMPLE_QUOTE, "Beutet man doch im Kriege gemästete Rinder und Schafe,\nUnd gewinnt Dreifüß' und braungemähnete Rosse;\nAber des Menschen Geist kehrt niemals,\nweder erbeutet, noch erlangt, \nnachdem er des Sterbenden Lippen entflohn ist.\n-Homer, Die Ilias; 9. Gesang"},
    {TR_BUILDING_MARS_TEMPLE_QUOTE, "Andere schufen für Mars ein Fahrzeug\nmit fliegenden Rädern, wie er es braucht,\num Menschen und Städte aufs Schlachtfeld zu hetzen.\n-Virgil, die Aeneis; achter Gesang" },
    {TR_BUILDING_VENUS_TEMPLE_QUOTE, "Venus du holde mitsamt dem beflügelten Sohne Cupido,\nOh, was empfand ich für Lust!\n Wie deutlich gefühltes Entzücken\nNahm mich dahin!\nWie lag ich gelöst im innersten Marke!\n-Ovid, Die Metamorphose; Byblis" },
    {TR_BUILDING_PANTHEON_QUOTE, "Weit auf tut sich indes des Olymps allmächtiges Haus,\nes Ruft zur Versammlung der Vater der Götter\nund König der Menschen.\nIn dem gestirnumstrahlten Palast,\nvon wo er auf alle Länder, der Dardaner Burg\nund Latiums Völker hinabschaut.\n-Virgil, Die Aeneis; Zehnter Gesang" },
    {TR_BUILDING_GRAND_TEMPLE_PHASE_1, "(Podium)"},
    {TR_BUILDING_GRAND_TEMPLE_PHASE_2, "(Portico)"},
    {TR_BUILDING_GRAND_TEMPLE_PHASE_3, "(Cella)"},
    {TR_BUILDING_GRAND_TEMPLE_PHASE_4, "(Praecinctum)"},
    {TR_BUILDING_GRAND_TEMPLE_PHASE_5, "(Dedicatio)"},
    {TR_BUILDING_GRAND_TEMPLE_PHASE_1_TEXT, "Bauarbeiter errichten das Podium, welches den Tempel emporheben und als solides Fundament dienen wird, um die Zeit zu überdauern." },
    {TR_BUILDING_GRAND_TEMPLE_PHASE_2_TEXT, "Handwerker fertigen den Portico, in welchem sich der Opferaltar des Tempels befindet." },
    {TR_BUILDING_GRAND_TEMPLE_PHASE_3_TEXT, "Baumeister errichten die Cella. In diesem innersten Raum des Tempels steht die Statue der Gottheit. Die Cella gilt als heiliger Ort der Gottheit. " },
    {TR_BUILDING_GRAND_TEMPLE_PHASE_4_TEXT, "Die Arbeit am Praecinctum hat begonnen, wo Gläubige sich für öffentliche Zeremonien versammeln." },
    {TR_BUILDING_GRAND_TEMPLE_PHASE_5_TEXT, "Mit dem Tempel beinahe fertiggestellt, sammeln sich Priester um die Rieten der Tempelweihe durchzuführen. " },
    {TR_BUILDING_MENU_TREES, "Bäume" },
    {TR_BUILDING_MENU_PATHS, "Pfade" },
    {TR_BUILDING_MENU_PARKS, "Parks"},
    {TR_BUILDING_SMALL_POND, "Kleiner Teich"},
    {TR_BUILDING_LARGE_POND, "Großer Teich"},
    {TR_BUILDING_PINE_TREE, "Pinie"},
    {TR_BUILDING_FIR_TREE, "Tanne" },
    {TR_BUILDING_OAK_TREE, "Eiche" },
    {TR_BUILDING_ELM_TREE, "Ulme" },
    {TR_BUILDING_FIG_TREE, "Feige" },
    {TR_BUILDING_PLUM_TREE, "Pflaume" },
    {TR_BUILDING_PALM_TREE, "Palme" },
    {TR_BUILDING_DATE_TREE, "Dattel" },
    {TR_BUILDING_PINE_PATH, "Pinienpfad" },
    {TR_BUILDING_FIR_PATH, "Tannenpfad" },
    {TR_BUILDING_OAK_PATH, "Eichenpfad" },
    {TR_BUILDING_ELM_PATH, "Ulmenpfad" },
    {TR_BUILDING_FIG_PATH, "Feigenpfad" },
    {TR_BUILDING_PLUM_PATH, "Pflaumenpfad" },
    {TR_BUILDING_PALM_PATH, "Palmenpfad" },
    {TR_BUILDING_DATE_PATH, "Dattelpfad" },
    {TR_BUILDING_BLUE_PAVILION, "Blauer Pavillon" },
    {TR_BUILDING_RED_PAVILION, "Roter Pavillon"},
    {TR_BUILDING_ORANGE_PAVILION, "Oranger Pavillon"},
    {TR_BUILDING_YELLOW_PAVILION, "Gelber Pavillon"},
    {TR_BUILDING_GREEN_PAVILION, "Grüner Pavillon" },
    {TR_BUILDING_SMALL_STATUE_ALT, "Göttinenstatue" },
    {TR_BUILDING_SMALL_STATUE_ALT_B, "Senatorenstatue"},
    {TR_BUILDING_OBELISK, "Obelisk" },
    {TR_BUILDING_POND_DESC, "Teiche füllen sich aus Reservoirs und versorgen Pflanzen und Tiere mit Wasser und als Oase der Natur dienen Einwohnern zur Entspannung. Alle Bewohner würden liebend gerne in der Nähe eines Teiches wohnen." },
    {TR_BUILDING_WINDOW_POND, "Teich"},
    {TR_BUILDING_OBELISK_DESC, "Ein prestigeträchtiges Monument, die Arbeit eines antiken König des Nils. Die Ägypter hatten keine Verwendung dafür."},
    {TR_ADVISOR_FINANCE_LEVIES, "Gebäudekosten"},
    {TR_CONFIRM_DELETE_MONUMENT, "Dieses Monument abreißen?"},
    {TR_SELECT_EPITHET_PROMPT_HEADER, "Beiname auswählen"},
    {TR_SELECT_EPITHET_PROMPT_TEXT, "Die Wahl eines Beinamens wird den Tempel unwiderruflich und dauerhaft auf einen Aspekt seiner Gottheit spezialisieren und die Priester mit göttlicher Macht erfüllen. Die kosten dafür betragen 1000 Dn." },
    {TR_BUILDING_INFO_MONTHLY_LEVY, "/Monat"},
    {TR_BUILDING_MESS_HALL, "Versorgungsposten"},
    {TR_BUILDING_MESS_HALL_DESC, "Der Versorgungsposten sammelt Nahrung aus Silos, um die Soldaten der Stadt zu versorgen. Ein schlecht versorgter Posten verlangsamt die Ausbildung neuer Soldaten und verringert die Moral der Truppen."},
    {TR_BUILDING_MESS_HALL_FULFILLMENT, "Versorgung des letzten Monats:"},
    {TR_BUILDING_MESS_HALL_TROOP_HUNGER, "Soldaten sind: " },
    {TR_BUILDING_MESS_HALL_TROOP_HUNGER_1, "Gut genährt" },
    {TR_BUILDING_MESS_HALL_TROOP_HUNGER_2, "Satt"},
    {TR_BUILDING_MESS_HALL_TROOP_HUNGER_3, "Hungrig"},
    {TR_BUILDING_MESS_HALL_TROOP_HUNGER_4, "Sehr hungrig"},
    {TR_BUILDING_MESS_HALL_TROOP_HUNGER_5, "Am Verhungern"},
    {TR_BUILDING_MESS_HALL_FOOD_TYPES_BONUS_1, "Die abwechslungsreiche Ernährung verbessert die Moral Eurer Soldaten."},
    {TR_BUILDING_MESS_HALL_FOOD_TYPES_BONUS_2, "Eure Soldaten genießen das vielfältige und reichhaltige Nahrungsangebot. Ihre Moral steigt enorm."},
    {TR_BUILDING_MESS_HALL_NO_SOLDIERS, "Ihr habt keine Soldaten zu ernähren." },
    {TR_BUILDING_MESS_HALL_MONTHS_FOOD_STORED, "Gelagerte Nahrung in Monaten:" },
    {TR_BUILDING_BARRACKS_FOOD_WARNING, "Nahrungsknappheit im Versorgungsposten verlangsamt die Ausbildung neuer Soldaten."},
    {TR_BUILDING_BARRACKS_FOOD_WARNING_2, "Kritische Nahrungsknappheiten an deinen Versorgungsposten verlangsamen die Sodatenrekrutierung." },
    {TR_BUILDING_LEGION_FOOD_WARNING_1, "Kürzliche Nahrungsknappheit verringert die Moral."},
    {TR_BUILDING_LEGION_FOOD_WARNING_2, "Kürzliche Nahrungsknappheit verringert die Moral enorm."},
    {TR_BUILDING_LEGION_STARVING, "Nahrungsmittelknappheit" },
    {TR_ADVISOR_LEGION_FOOD_SATISFIED, "Eure Soldaten haben ausreichend Nahrung."},
    {TR_ADVISOR_LEGION_FOOD_NEEDED, "Eure Soldaten benötigen mehr Nahrung." },
    {TR_ADVISOR_LEGION_FOOD_CRITICAL, "Eure Soldaten verhungern!"},
    {TR_ADVISOR_LEGION_MONTHS_FOOD_STORED, "Gelagerter Nahrung im Versorgungsposten in Monaten:" },
    {TR_CITY_MESSAGE_TITLE_MESS_HALL_NEEDS_FOOD, "Hungrige Soldaten" },
    {TR_CITY_MESSAGE_TEXT_MESS_HALL_NEEDS_FOOD, "In Eurem Versorgungsposten befindet sich sehr wenig Nahrung und die Moral der Truppen schwindet. Stellen Sie sicher, der Versorgungsposten Zugang zu einem gut gefüllten Silo hat."},
    {TR_CITY_MESSAGE_TEXT_MESS_HALL_MISSING, "Eure Stadt hat den Versorgungsposten verloren und Eure Soldaten hungern! Bauen Sie umgehend einen neuen!"},
    {TR_MARKET_SPECIAL_ORDERS_HEADER, "Zu sammelnde Waren"},
    {TR_WARNING_NO_MESS_HALL, "Ihr müsst zunächst einen Versorgungsposten bauen, um eure Soldaten zu ernähren." },
    {TR_WARNING_MAX_GRAND_TEMPLES, "In einer Stadt können nur maximal zwei Prachttempel gebaut werden." },
    {TR_CITY_MESSAGE_TITLE_GRAND_TEMPLE_COMPLETE, "Prachttempel fertiggestellt"},
    {TR_CITY_MESSAGE_TEXT_GRAND_TEMPLE_COMPLETE, "Priester und Verehrer der Gottheit sammeln sich für die Riten der Tempelweihe in Scharen am neuen Prachttempel. Eure Einwohner bewundern das majestätische Bauwerk und die Gottheit überhäuft Euch mit ihrer Gunst."},
    {TR_CITY_MESSAGE_TITLE_MERCURY_BLESSING, "Eine Segnung des Merkur" },
    {TR_CITY_MESSAGE_TEXT_MERCURY_BLESSING, "Hocherfreut von Eurer Hingabe, hat Merkur die Industrie der Stadt gesegnet und Eure Lager mit Rohmaterialien gefüllt."},
    {TR_FIGURE_TYPE_WORK_CAMP_WORKER, "Vorarbeiter"},
    {TR_FIGURE_TYPE_WORK_CAMP_SLAVE, "Träger"},
    {TR_FIGURE_TYPE_WORK_CAMP_ENGINEER, "Baumeister"},
    {TR_FIGURE_TYPE_MESS_HALL_BUYER, "Quartiermeister"},
    {TR_FIGURE_TYPE_MESS_HALL_COLLECTOR, "Lagerarbeiter"},
    {TR_BUILDING_CERES_TEMPLE_MODULE_DESC, "Die Priester des Prachttempels der Ceres unterstützen die Versorgung hungriger Einwohner mit Nahrung und Öl."},
    {TR_BUILDING_VENUS_TEMPLE_MODULE_DESC, "Der Prachttempel der Venus ermöglicht ihren Priestern, die Bevölkerung mit gesegnetem Wein zu versorgen." },
    {TR_BUILDING_MARS_TEMPLE_MODULE_DESC, "Die Priester des Prachttempels des Mars sammeln Lebensmittelspenden für eure Truppen, um diese an den Versorgungsposten zu liefern."},
    {TR_BUILDING_SMALL_TEMPLE_CERES_NAME, "Tempel der Ceres"},
    {TR_BUILDING_SMALL_TEMPLE_NEPTUNE_NAME, "Tempel des Neptun"},
    {TR_BUILDING_SMALL_TEMPLE_MERCURY_NAME, "Tempel des Merkur"},
    {TR_BUILDING_SMALL_TEMPLE_MARS_NAME, "Tempel des Mars"},
    {TR_BUILDING_SMALL_TEMPLE_VENUS_NAME, "Tempel der Venus"},
    {TR_FIGURE_TYPE_PRIEST_BUYER, "Priester" },
    // Transkription von mission_exact4.wav
    {TR_PHRASE_FIGURE_MISSIONARY_EXACT_4, "\"Ich werde tun, was ich kann, um diese Barbaren zu beruhigen. Ich bin sicher, dass sie ihre Angriffe auf die Stadt einstellen werden, wenn ich einfach nur mit ihnen spreche.\"" },
    {TR_CITY_MESSAGE_TITLE_PANTHEON_FESTIVAL, "Ein jährliches Fest"},
    {TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_CERES, "Die Gläubigen strömen zu Tempeln, um Cerealia zu Ehren von Ceres zu feiern. Landwirte bringen Opfer für reiche Ernten in den kommenden Jahren."},
    {TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_NEPTUNE, "Heute ist das Fest von Neptunalia zu Ehren des Neptun. Die Gläubigen bauen Hütten aus Ästen und Blattwerk und feiern fröhlich unter der lodernden Hitze der Mittsommersonne."},
    {TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_MERCURY, "Händler und Kaufleute feiern in Scharen Mercuralia. In der Hoffnung auf göttlichen Schutz durch den Gott Merkur wird heiliges Wasser auf Schiffe und Lagerhäuser gespritzt."},
    {TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_MARS, "Die Bürger versammeln sich außerhalb der Stadt zur Feier von Equirria, um die Gunst des Mars zu ersuchen. Die Luft ist erfüllt vom Donner der Hufe und dem Knarren der Streitwagen, wenn Gläubige Rennen zu Ehren ihres Gottes veranstalten."},
    {TR_CITY_MESSAGE_TEXT_PANTHEON_FESTIVAL_VENUS, "Die Gläubigen versammeln sich zur Feier von Veneralia, einem Tag, der der Venus heilig ist. Ihre Bürger bitten sie um Glück in Herzensangelegenheiten."},
    {TR_TOOLTIP_BUTTON_DELETE_READ_MESSAGES, "Gelesene Nachrichten löschen"},
    {TR_TOOLTIP_BUTTON_MOTHBALL_ON, "Gebäude deaktivieren"},
    {TR_TOOLTIP_BUTTON_MOTHBALL_OFF, "Gebäude aktivieren"},
    {TR_TOOLTIP_BUTTON_ACCEPT_MARKET_LADIES, "Erlaube Marktfrauen von hier Waren zu holen"},
    {TR_TOOLTIP_BUTTON_ACCEPT_TRADE_CARAVAN, "Erlaube Karawanen hier Handel zu treiben"},
    {TR_TOOLTIP_BUTTON_ACCEPT_TRADE_SHIPS, "Erlaube Handelsschiffen hier Handel zu treiben"},
    {TR_CONFIG_HEADER_CITY_MANAGEMENT_CHANGES, "Stadtverwaltung"},
    {TR_BUILDING_LIGHTHOUSE, "Leuchtturm"},
    {TR_BUILDING_LIGHTHOUSE_PHASE_1, "(Fundament)" },
    {TR_BUILDING_LIGHTHOUSE_PHASE_2, "(Sockel)" },
    {TR_BUILDING_LIGHTHOUSE_PHASE_3, "(Turm)" },
    {TR_BUILDING_LIGHTHOUSE_PHASE_4, "(First)" },
    {TR_BUILDING_LIGHTHOUSE_PHASE_1_TEXT, "Bauarbeiter legen ein starkes Fundament, um das Gewicht eines großen steinernen Turms zu tragen." },
    {TR_BUILDING_LIGHTHOUSE_PHASE_2_TEXT, "Baumeister konstruieren den Sockel, der die Flamme des Leuchtturms weit über den Hoizont erheben wird." },
    {TR_BUILDING_LIGHTHOUSE_PHASE_3_TEXT, "Der Leuchtturm wächst jeden Tag etwas höher, während die Bauarbeiter ihre Arbeit verrichten." },
    {TR_BUILDING_LIGHTHOUSE_PHASE_4_TEXT, "Baumeister geben dem Leuchtturm den letzten Schliff. Bald schon wird er kilometerweit leuchten und Schiffen den Weg weisen." },
    {TR_BUILDING_LIGHTHOUSE_CONSTRUCTION_DESC, "Die Konstruktion des Leuchtturms benötigt gelagerte Materialien aus einem Lagerhaus, Bauarbeiter aus einem Arbeiterlager und Baumeister einer Baumeister Gilde." },
    {TR_BUILDING_LIGHTHOUSE_BONUS_DESC, "Fischerboote bewegen sich 10% schneller und eine stürmische See beruhigt sich doppelt so schnell." },
    {TR_EDITOR_ALLOWED_BUILDINGS_MONUMENTS, "Monumente"},
    {TR_CITY_MESSAGE_TEXT_LIGHTHOUSE_COMPLETE, "Der fertige Leuchtturm, ein mächtiger Turm aus Stein, der über den Horizont ragt. Möge sein Leuchtfeuer Seefahrer bis zum Ende der Zeit nach Hause leiten." },
    {TR_CITY_MESSAGE_TEXT_PANTHEON_COMPLETE, "Das Pantheon ist fertiggestellt. Unerreicht steht es als Monument für die großartige Macht der Götter und dem Volke Roms." },
    {TR_CITY_MESSAGE_TITLE_MONUMENT_COMPLETE, "Monument fertiggestellt" },
    {TR_CITY_MESSAGE_TITLE_NEPTUNE_BLESSING, "Eine Segnung von Neptun"},
    {TR_CITY_MESSAGE_TEXT_NEPTUNE_BLESSING, "Neptun belohnt die Hingabe eurer Einwohner und garantiert Seefahrern eine sichere Überfahrt für 12 Monate und 50% mehr Einnahmen aus Exporten in diesem Zeitraum."},
    {TR_CITY_MESSAGE_TITLE_VENUS_BLESSING, "Eine Segnung von Venus" },
    {TR_CITY_MESSAGE_TEXT_VENUS_BLESSING, "Erfreut über die Ehrfurcht, die ihr entgegengebracht wird, verleiht Venus Eurem Volk Jugendlichkeit, Gesundheit und Glück und erhöht so die Größe Eurer arbeitenden Bevölkerung." },
    {TR_BUILDING_MENU_STATUES, "Statuen" },
    {TR_BUILDING_MENU_GOV_RES, "Gouverneursanwesen" },
    {TR_OVERLAY_ROADS, "Straßen" },
    {TR_NO_MODS_TITLE, "Mods Ordner konnte nicht gefunden werden." },
    {TR_NO_MODS_MESSAGE,
    "In Ihrer Caesar 3-Installation ist der Mods-Ordner nicht ordnungsgemäß installiert."
    "Neue Spielinhalte werden nicht richtig angezeigt.\n"
    "Stellen Sie sicher, dass ein '/mods'-Verzeichnis in der obersten Ebene Ihres Caesar 3-Installationsverzeichnisses vorhanden ist."},
    {TR_WARNING_WATER_NEEDED_FOR_LIGHTHOUSE, "Leuchtturm muss nah am Wasser platziert werden."},
    {TR_TOOLTIP_OVERLAY_PANTHEON_ACCESS, "Dieses Haus hat durch das Pantheon Zugang zu allen fünf Göttern."},
    {TR_BUILDING_LEGION_FOOD_BONUS, "Reichhaltiges Nahrungsangebot steigert die Moral" },
    {TR_BUILDING_LEGION_FOOD_STATUS, "Versorgungsstatus"},
    {TR_TOOLTIP_BUTTON_ACCEPT_QUARTERMASTER, "Erlaube Quartiermeister von hier Nahrung zu holen"},
    {TR_WARNING_RESOURCES_NOT_AVAILABLE, "Sie können die benötigten Waren nicht erhalten."},
    {TR_CONFIG_GP_CH_MONUMENTS_BOOST_CULTURE_RATING, "Abgeschlossene Prachttempel gewähren eine Kulturbewertung von +8"},
    {TR_BUTTON_BACK_TO_MAIN_MENU, "Zurück zum Hauptmenü" },
    {TR_LABEL_PAUSE_MENU, "Pause" },
    {TR_OVERLAY_LEVY, "Abgaben" },
    {TR_TOOLTIP_OVERLAY_LEVY, " Monatlich Abgaben in Denarii." },
    {TR_MAP_EDITOR_OPTIONS, "Szenario Einstellungen" }
    {TR_BUILDING_MARS_TEMPLE_MODULE_DESC_NO_MESS, "Dieser Tempel wird Essen für deinen Versorgungsposten sammeln, sobald er gebaut wurde." },

};

void translation_german(const translation_string **strings, int *num_strings)
{
    *strings = all_strings;
    *num_strings = sizeof(all_strings) / sizeof(translation_string);
}
