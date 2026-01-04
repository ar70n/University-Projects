<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="CLK" />
        <signal name="XLXN_14" />
        <signal name="Q0" />
        <signal name="Q3" />
        <signal name="XLXN_18" />
        <signal name="CLR" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q2" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q3" />
        <port polarity="Input" name="CLR" />
        <blockdef name="fdc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
        <blockdef name="and2b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
        </blockdef>
        <block symbolname="fdc" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_19" name="CLR" />
            <blockpin signalname="XLXN_4" name="D" />
            <blockpin signalname="Q0" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_19" name="CLR" />
            <blockpin signalname="Q0" name="D" />
            <blockpin signalname="Q1" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_19" name="CLR" />
            <blockpin signalname="Q1" name="D" />
            <blockpin signalname="Q2" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_19" name="CLR" />
            <blockpin signalname="Q2" name="D" />
            <blockpin signalname="Q3" name="Q" />
        </block>
        <block symbolname="vcc" name="XLXI_5">
            <blockpin signalname="XLXN_4" name="P" />
        </block>
        <block symbolname="or2" name="XLXI_9">
            <blockpin signalname="CLR" name="I0" />
            <blockpin signalname="XLXN_18" name="I1" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_10">
            <blockpin signalname="CLK" name="I0" />
            <blockpin signalname="Q3" name="I1" />
            <blockpin signalname="XLXN_18" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1296" y="1408" name="XLXI_2" orien="R0" />
        <instance x="1840" y="1408" name="XLXI_3" orien="R0" />
        <instance x="2320" y="1408" name="XLXI_4" orien="R0" />
        <instance x="800" y="1408" name="XLXI_1" orien="R0" />
        <branch name="Q1">
            <wire x2="1760" y1="1152" y2="1152" x1="1680" />
            <wire x2="1840" y1="1152" y2="1152" x1="1760" />
            <wire x2="1760" y1="944" y2="944" x1="1744" />
            <wire x2="1760" y1="944" y2="1152" x1="1760" />
        </branch>
        <branch name="Q2">
            <wire x2="2272" y1="1152" y2="1152" x1="2224" />
            <wire x2="2320" y1="1152" y2="1152" x1="2272" />
            <wire x2="2272" y1="928" y2="928" x1="2256" />
            <wire x2="2272" y1="928" y2="1152" x1="2272" />
        </branch>
        <instance x="400" y="1152" name="XLXI_5" orien="R0" />
        <branch name="XLXN_4">
            <wire x2="464" y1="1152" y2="1216" x1="464" />
            <wire x2="560" y1="1216" y2="1216" x1="464" />
            <wire x2="560" y1="1152" y2="1216" x1="560" />
            <wire x2="800" y1="1152" y2="1152" x1="560" />
        </branch>
        <iomarker fontsize="28" x="256" y="1536" name="CLR" orien="R180" />
        <branch name="CLK">
            <wire x2="288" y1="1696" y2="1792" x1="288" />
            <wire x2="320" y1="1792" y2="1792" x1="288" />
            <wire x2="320" y1="1792" y2="1840" x1="320" />
            <wire x2="320" y1="1840" y2="1952" x1="320" />
            <wire x2="688" y1="1840" y2="1840" x1="320" />
            <wire x2="1264" y1="1840" y2="1840" x1="688" />
            <wire x2="1744" y1="1840" y2="1840" x1="1264" />
            <wire x2="2288" y1="1840" y2="1840" x1="1744" />
            <wire x2="352" y1="1696" y2="1696" x1="288" />
            <wire x2="688" y1="1280" y2="1840" x1="688" />
            <wire x2="800" y1="1280" y2="1280" x1="688" />
            <wire x2="1264" y1="1280" y2="1840" x1="1264" />
            <wire x2="1296" y1="1280" y2="1280" x1="1264" />
            <wire x2="1744" y1="1280" y2="1840" x1="1744" />
            <wire x2="1840" y1="1280" y2="1280" x1="1744" />
            <wire x2="2288" y1="1280" y2="1840" x1="2288" />
            <wire x2="2320" y1="1280" y2="1280" x1="2288" />
        </branch>
        <branch name="Q0">
            <wire x2="1248" y1="1152" y2="1152" x1="1184" />
            <wire x2="1296" y1="1152" y2="1152" x1="1248" />
            <wire x2="1264" y1="912" y2="912" x1="1248" />
            <wire x2="1248" y1="912" y2="1152" x1="1248" />
        </branch>
        <iomarker fontsize="28" x="1264" y="912" name="Q0" orien="R0" />
        <iomarker fontsize="28" x="1744" y="944" name="Q1" orien="R180" />
        <iomarker fontsize="28" x="2256" y="928" name="Q2" orien="R180" />
        <iomarker fontsize="28" x="320" y="1952" name="CLK" orien="R90" />
        <branch name="Q3">
            <attrtext style="alignment:SOFT-TVCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2752" y="992" type="branch" />
            <wire x2="320" y1="1584" y2="1664" x1="320" />
            <wire x2="336" y1="1664" y2="1664" x1="320" />
            <wire x2="2784" y1="1584" y2="1584" x1="320" />
            <wire x2="336" y1="1632" y2="1664" x1="336" />
            <wire x2="352" y1="1632" y2="1632" x1="336" />
            <wire x2="2752" y1="1152" y2="1152" x1="2704" />
            <wire x2="2784" y1="1152" y2="1152" x1="2752" />
            <wire x2="2784" y1="1152" y2="1584" x1="2784" />
            <wire x2="2752" y1="912" y2="912" x1="2736" />
            <wire x2="2752" y1="912" y2="992" x1="2752" />
            <wire x2="2752" y1="992" y2="1152" x1="2752" />
        </branch>
        <iomarker fontsize="28" x="2736" y="912" name="Q3" orien="R180" />
        <instance x="528" y="2048" name="XLXI_9" orien="R0" />
        <branch name="XLXN_18">
            <wire x2="448" y1="1856" y2="1920" x1="448" />
            <wire x2="528" y1="1920" y2="1920" x1="448" />
            <wire x2="672" y1="1856" y2="1856" x1="448" />
            <wire x2="672" y1="1664" y2="1664" x1="608" />
            <wire x2="672" y1="1664" y2="1856" x1="672" />
        </branch>
        <branch name="CLR">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="288" y="1536" type="branch" />
            <wire x2="288" y1="1536" y2="1536" x1="256" />
            <wire x2="400" y1="1536" y2="1536" x1="288" />
            <wire x2="400" y1="1520" y2="1520" x1="304" />
            <wire x2="400" y1="1520" y2="1536" x1="400" />
            <wire x2="304" y1="1520" y2="1728" x1="304" />
            <wire x2="528" y1="1728" y2="1728" x1="304" />
            <wire x2="528" y1="1728" y2="1792" x1="528" />
            <wire x2="464" y1="1792" y2="1984" x1="464" />
            <wire x2="528" y1="1984" y2="1984" x1="464" />
            <wire x2="528" y1="1792" y2="1792" x1="464" />
        </branch>
        <branch name="XLXN_19">
            <wire x2="800" y1="1952" y2="1952" x1="784" />
            <wire x2="1296" y1="1952" y2="1952" x1="800" />
            <wire x2="1840" y1="1952" y2="1952" x1="1296" />
            <wire x2="2320" y1="1952" y2="1952" x1="1840" />
            <wire x2="800" y1="1376" y2="1952" x1="800" />
            <wire x2="1296" y1="1376" y2="1952" x1="1296" />
            <wire x2="1840" y1="1376" y2="1952" x1="1840" />
            <wire x2="2320" y1="1376" y2="1952" x1="2320" />
        </branch>
        <instance x="352" y="1760" name="XLXI_10" orien="R0" />
    </sheet>
</drawing>