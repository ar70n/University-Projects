<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="A" />
        <signal name="B" />
        <signal name="XLXN_4" />
        <signal name="XLXN_6" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="C" />
        <signal name="D" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="Z" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
        <port polarity="Output" name="Z" />
        <blockdef name="d3_8e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-320" y2="-320" x1="384" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <rect width="256" x="64" y="-640" height="576" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="or6">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="48" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-320" y2="-320" x1="0" />
            <line x2="48" y1="-384" y2="-384" x1="0" />
            <line x2="192" y1="-224" y2="-224" x1="256" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <arc ex="112" ey="-272" sx="192" sy="-224" r="88" cx="116" cy="-184" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
            <arc ex="192" ey="-224" sx="112" sy="-176" r="88" cx="116" cy="-264" />
            <arc ex="48" ey="-272" sx="48" sy="-176" r="56" cx="16" cy="-224" />
            <line x2="48" y1="-272" y2="-272" x1="112" />
            <line x2="48" y1="-64" y2="-176" x1="48" />
            <line x2="48" y1="-272" y2="-384" x1="48" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="d3_8e" name="XLXI_1">
            <blockpin signalname="D" name="A0" />
            <blockpin signalname="C" name="A1" />
            <blockpin signalname="B" name="A2" />
            <blockpin signalname="XLXN_17" name="E" />
            <blockpin name="D0" />
            <blockpin name="D1" />
            <blockpin name="D2" />
            <blockpin signalname="XLXN_10" name="D3" />
            <blockpin signalname="XLXN_11" name="D4" />
            <blockpin signalname="XLXN_12" name="D5" />
            <blockpin name="D6" />
            <blockpin name="D7" />
        </block>
        <block symbolname="d3_8e" name="XLXI_2">
            <blockpin signalname="D" name="A0" />
            <blockpin signalname="C" name="A1" />
            <blockpin signalname="B" name="A2" />
            <blockpin signalname="A" name="E" />
            <blockpin signalname="XLXN_13" name="D0" />
            <blockpin name="D1" />
            <blockpin name="D2" />
            <blockpin name="D3" />
            <blockpin name="D4" />
            <blockpin signalname="XLXN_15" name="D5" />
            <blockpin name="D6" />
            <blockpin signalname="XLXN_14" name="D7" />
        </block>
        <block symbolname="or6" name="XLXI_3">
            <blockpin signalname="XLXN_14" name="I0" />
            <blockpin signalname="XLXN_15" name="I1" />
            <blockpin signalname="XLXN_13" name="I2" />
            <blockpin signalname="XLXN_12" name="I3" />
            <blockpin signalname="XLXN_11" name="I4" />
            <blockpin signalname="XLXN_10" name="I5" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_4">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_17" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1008" y="1072" name="XLXI_1" orien="R0" />
        <branch name="D">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="192" y="480" type="branch" />
            <wire x2="192" y1="480" y2="480" x1="128" />
            <wire x2="256" y1="480" y2="480" x1="192" />
            <wire x2="544" y1="480" y2="480" x1="256" />
            <wire x2="544" y1="480" y2="496" x1="544" />
            <wire x2="1008" y1="496" y2="496" x1="544" />
            <wire x2="256" y1="480" y2="576" x1="256" />
            <wire x2="480" y1="576" y2="576" x1="256" />
            <wire x2="480" y1="576" y2="1184" x1="480" />
            <wire x2="1008" y1="1184" y2="1184" x1="480" />
        </branch>
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="272" y="736" type="branch" />
            <wire x2="272" y1="736" y2="736" x1="208" />
            <wire x2="400" y1="736" y2="736" x1="272" />
            <wire x2="496" y1="736" y2="736" x1="400" />
            <wire x2="496" y1="736" y2="1248" x1="496" />
            <wire x2="1008" y1="1248" y2="1248" x1="496" />
            <wire x2="400" y1="560" y2="736" x1="400" />
            <wire x2="1008" y1="560" y2="560" x1="400" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="256" y="848" type="branch" />
            <wire x2="256" y1="848" y2="848" x1="176" />
            <wire x2="336" y1="848" y2="848" x1="256" />
            <wire x2="528" y1="848" y2="848" x1="336" />
            <wire x2="336" y1="848" y2="1312" x1="336" />
            <wire x2="1008" y1="1312" y2="1312" x1="336" />
            <wire x2="528" y1="624" y2="848" x1="528" />
            <wire x2="1008" y1="624" y2="624" x1="528" />
        </branch>
        <instance x="1008" y="1760" name="XLXI_2" orien="R0" />
        <iomarker fontsize="28" x="688" y="1856" name="A" orien="R180" />
        <iomarker fontsize="28" x="176" y="848" name="B" orien="R180" />
        <iomarker fontsize="28" x="208" y="736" name="C" orien="R180" />
        <iomarker fontsize="28" x="128" y="480" name="D" orien="R180" />
        <instance x="1952" y="1184" name="XLXI_3" orien="R0" />
        <branch name="XLXN_10">
            <wire x2="1952" y1="688" y2="688" x1="1392" />
            <wire x2="1952" y1="688" y2="800" x1="1952" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="1664" y1="752" y2="752" x1="1392" />
            <wire x2="1664" y1="752" y2="864" x1="1664" />
            <wire x2="1952" y1="864" y2="864" x1="1664" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="1648" y1="816" y2="816" x1="1392" />
            <wire x2="1648" y1="816" y2="928" x1="1648" />
            <wire x2="1952" y1="928" y2="928" x1="1648" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="1664" y1="1184" y2="1184" x1="1392" />
            <wire x2="1664" y1="992" y2="1184" x1="1664" />
            <wire x2="1952" y1="992" y2="992" x1="1664" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="1952" y1="1632" y2="1632" x1="1392" />
            <wire x2="1952" y1="1120" y2="1632" x1="1952" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="1680" y1="1504" y2="1504" x1="1392" />
            <wire x2="1680" y1="1056" y2="1504" x1="1680" />
            <wire x2="1952" y1="1056" y2="1056" x1="1680" />
        </branch>
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2288" y="960" type="branch" />
            <wire x2="2288" y1="960" y2="960" x1="2208" />
            <wire x2="2368" y1="960" y2="960" x1="2288" />
        </branch>
        <iomarker fontsize="28" x="2368" y="960" name="Z" orien="R0" />
        <instance x="624" y="1104" name="XLXI_4" orien="R0" />
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="720" y="1856" type="branch" />
            <wire x2="624" y1="1072" y2="1072" x1="576" />
            <wire x2="576" y1="1072" y2="1168" x1="576" />
            <wire x2="800" y1="1168" y2="1168" x1="576" />
            <wire x2="800" y1="1168" y2="1632" x1="800" />
            <wire x2="832" y1="1632" y2="1632" x1="800" />
            <wire x2="1008" y1="1632" y2="1632" x1="832" />
            <wire x2="720" y1="1856" y2="1856" x1="688" />
            <wire x2="784" y1="1856" y2="1856" x1="720" />
            <wire x2="784" y1="1632" y2="1856" x1="784" />
            <wire x2="800" y1="1632" y2="1632" x1="784" />
        </branch>
        <branch name="XLXN_17">
            <wire x2="928" y1="1072" y2="1072" x1="848" />
            <wire x2="928" y1="944" y2="1072" x1="928" />
            <wire x2="1008" y1="944" y2="944" x1="928" />
        </branch>
    </sheet>
</drawing>