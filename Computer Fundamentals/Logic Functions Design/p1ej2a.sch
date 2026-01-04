<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="Z" />
        <signal name="A" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="B" />
        <signal name="D" />
        <signal name="C" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="C" />
        <blockdef name="and2b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="and3b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="and3b3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="40" y1="-192" y2="-192" x1="0" />
            <circle r="12" cx="52" cy="-192" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
        </blockdef>
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <block symbolname="and2b2" name="XLXI_1">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_2">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="B" name="I2" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="and3b3" name="XLXI_3">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="B" name="I2" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_4">
            <blockpin signalname="XLXN_1" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="XLXN_3" name="I2" />
            <blockpin signalname="Z" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="752" y="944" name="XLXI_1" orien="R0" />
        <instance x="752" y="1248" name="XLXI_2" orien="R0" />
        <instance x="752" y="1504" name="XLXI_3" orien="R0" />
        <instance x="1728" y="1248" name="XLXI_4" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1728" y1="1376" y2="1376" x1="1008" />
            <wire x2="1728" y1="1184" y2="1376" x1="1728" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1728" y1="1120" y2="1120" x1="1008" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1728" y1="848" y2="848" x1="1008" />
            <wire x2="1728" y1="848" y2="1056" x1="1728" />
        </branch>
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2064" y="1120" type="branch" />
            <wire x2="2064" y1="1120" y2="1120" x1="1984" />
            <wire x2="2240" y1="1120" y2="1120" x1="2064" />
        </branch>
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="704" y="816" type="branch" />
            <wire x2="704" y1="816" y2="816" x1="512" />
            <wire x2="752" y1="816" y2="816" x1="704" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="272" y="880" type="branch" />
            <wire x2="272" y1="880" y2="880" x1="224" />
            <wire x2="352" y1="880" y2="880" x1="272" />
            <wire x2="512" y1="880" y2="880" x1="352" />
            <wire x2="544" y1="880" y2="880" x1="512" />
            <wire x2="752" y1="880" y2="880" x1="544" />
            <wire x2="544" y1="880" y2="1056" x1="544" />
            <wire x2="752" y1="1056" y2="1056" x1="544" />
            <wire x2="352" y1="880" y2="1312" x1="352" />
            <wire x2="528" y1="1312" y2="1312" x1="352" />
            <wire x2="752" y1="1312" y2="1312" x1="528" />
        </branch>
        <branch name="D">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="256" y="1120" type="branch" />
            <wire x2="256" y1="1120" y2="1120" x1="176" />
            <wire x2="448" y1="1120" y2="1120" x1="256" />
            <wire x2="480" y1="1120" y2="1120" x1="448" />
            <wire x2="528" y1="1120" y2="1120" x1="480" />
            <wire x2="752" y1="1120" y2="1120" x1="528" />
            <wire x2="480" y1="1120" y2="1392" x1="480" />
            <wire x2="528" y1="1392" y2="1392" x1="480" />
            <wire x2="752" y1="1376" y2="1376" x1="528" />
            <wire x2="528" y1="1376" y2="1392" x1="528" />
        </branch>
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="240" y="1184" type="branch" />
            <wire x2="240" y1="1184" y2="1184" x1="192" />
            <wire x2="384" y1="1184" y2="1184" x1="240" />
            <wire x2="384" y1="1184" y2="1440" x1="384" />
            <wire x2="512" y1="1440" y2="1440" x1="384" />
            <wire x2="752" y1="1440" y2="1440" x1="512" />
            <wire x2="512" y1="1184" y2="1184" x1="384" />
            <wire x2="752" y1="1184" y2="1184" x1="512" />
        </branch>
        <iomarker fontsize="28" x="224" y="880" name="B" orien="R180" />
        <iomarker fontsize="28" x="512" y="816" name="A" orien="R180" />
        <iomarker fontsize="28" x="176" y="1120" name="D" orien="R180" />
        <iomarker fontsize="28" x="192" y="1184" name="C" orien="R180" />
        <iomarker fontsize="28" x="2240" y="1120" name="Z" orien="R0" />
    </sheet>
</drawing>