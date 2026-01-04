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
        <signal name="XLXN_4" />
        <signal name="Z" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="D" />
        <signal name="XLXN_9" />
        <signal name="C" />
        <signal name="XLXN_13" />
        <signal name="B" />
        <signal name="XLXN_15" />
        <signal name="A" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="A" />
        <blockdef name="or2b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="32" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="44" cy="-64" />
            <line x2="32" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="44" cy="-128" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
        </blockdef>
        <blockdef name="or2b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="32" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="44" cy="-64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
        </blockdef>
        <blockdef name="or3b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="28" y1="-64" y2="-64" x1="0" />
            <circle r="10" cx="38" cy="-62" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="60" cy="-128" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-128" y2="-128" x1="40" />
        </blockdef>
        <blockdef name="and4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-112" y2="-112" x1="144" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-64" y2="-64" x1="0" />
        </blockdef>
        <block symbolname="or2b2" name="XLXI_1">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="or2b1" name="XLXI_2">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="or2b2" name="XLXI_3">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="or3b2" name="XLXI_4">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="B" name="I2" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_5">
            <blockpin signalname="XLXN_1" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="XLXN_3" name="I2" />
            <blockpin signalname="XLXN_4" name="I3" />
            <blockpin signalname="Z" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="784" y="720" name="XLXI_1" orien="R0" />
        <instance x="784" y="976" name="XLXI_2" orien="R0" />
        <instance x="800" y="1248" name="XLXI_3" orien="R0" />
        <instance x="816" y="1552" name="XLXI_4" orien="R0" />
        <instance x="1824" y="1168" name="XLXI_5" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1824" y1="1424" y2="1424" x1="1072" />
            <wire x2="1824" y1="1104" y2="1424" x1="1824" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1440" y1="1152" y2="1152" x1="1056" />
            <wire x2="1440" y1="1040" y2="1152" x1="1440" />
            <wire x2="1824" y1="1040" y2="1040" x1="1440" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1424" y1="880" y2="880" x1="1040" />
            <wire x2="1424" y1="880" y2="976" x1="1424" />
            <wire x2="1824" y1="976" y2="976" x1="1424" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1824" y1="624" y2="624" x1="1040" />
            <wire x2="1824" y1="624" y2="912" x1="1824" />
        </branch>
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2192" y="1008" type="branch" />
            <wire x2="2192" y1="1008" y2="1008" x1="2080" />
            <wire x2="2352" y1="1008" y2="1008" x1="2192" />
        </branch>
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="208" y="592" type="branch" />
            <wire x2="208" y1="592" y2="592" x1="112" />
            <wire x2="336" y1="592" y2="592" x1="208" />
            <wire x2="384" y1="592" y2="592" x1="336" />
            <wire x2="448" y1="592" y2="592" x1="384" />
            <wire x2="784" y1="592" y2="592" x1="448" />
            <wire x2="384" y1="592" y2="1120" x1="384" />
            <wire x2="464" y1="1120" y2="1120" x1="384" />
            <wire x2="800" y1="1120" y2="1120" x1="464" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="176" y="912" type="branch" />
            <wire x2="176" y1="912" y2="912" x1="80" />
            <wire x2="240" y1="912" y2="912" x1="176" />
            <wire x2="288" y1="912" y2="912" x1="240" />
            <wire x2="336" y1="912" y2="912" x1="288" />
            <wire x2="464" y1="912" y2="912" x1="336" />
            <wire x2="784" y1="912" y2="912" x1="464" />
            <wire x2="288" y1="912" y2="1360" x1="288" />
            <wire x2="480" y1="1360" y2="1360" x1="288" />
            <wire x2="816" y1="1360" y2="1360" x1="480" />
            <wire x2="448" y1="656" y2="656" x1="336" />
            <wire x2="784" y1="656" y2="656" x1="448" />
            <wire x2="336" y1="656" y2="912" x1="336" />
        </branch>
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="224" y="1184" type="branch" />
            <wire x2="224" y1="1184" y2="1184" x1="112" />
            <wire x2="368" y1="1184" y2="1184" x1="224" />
            <wire x2="400" y1="1184" y2="1184" x1="368" />
            <wire x2="464" y1="1184" y2="1184" x1="400" />
            <wire x2="800" y1="1184" y2="1184" x1="464" />
            <wire x2="400" y1="1184" y2="1488" x1="400" />
            <wire x2="448" y1="1488" y2="1488" x1="400" />
            <wire x2="464" y1="1488" y2="1488" x1="448" />
            <wire x2="816" y1="1488" y2="1488" x1="464" />
        </branch>
        <branch name="D">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="208" y="1424" type="branch" />
            <wire x2="208" y1="1424" y2="1424" x1="96" />
            <wire x2="464" y1="1424" y2="1424" x1="208" />
            <wire x2="480" y1="1424" y2="1424" x1="464" />
            <wire x2="816" y1="1424" y2="1424" x1="480" />
            <wire x2="464" y1="848" y2="848" x1="448" />
            <wire x2="784" y1="848" y2="848" x1="464" />
            <wire x2="448" y1="848" y2="1248" x1="448" />
            <wire x2="464" y1="1248" y2="1248" x1="448" />
            <wire x2="464" y1="1248" y2="1424" x1="464" />
        </branch>
        <iomarker fontsize="28" x="2352" y="1008" name="Z" orien="R0" />
        <iomarker fontsize="28" x="112" y="592" name="C" orien="R180" />
        <iomarker fontsize="28" x="80" y="912" name="B" orien="R180" />
        <iomarker fontsize="28" x="112" y="1184" name="A" orien="R180" />
        <iomarker fontsize="28" x="96" y="1424" name="D" orien="R180" />
    </sheet>
</drawing>