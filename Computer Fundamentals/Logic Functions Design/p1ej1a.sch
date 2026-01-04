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
        <signal name="D" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="Z" />
        <signal name="C" />
        <signal name="A" />
        <signal name="B" />
        <port polarity="Input" name="D" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="and3" name="XLXI_1">
            <blockpin signalname="XLXN_3" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="XLXN_1" name="I2" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_3">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="XLXN_7" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_4">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="992" y="1312" name="XLXI_1" orien="R0" />
        <instance x="976" y="1520" name="XLXI_2" orien="R0" />
        <instance x="1584" y="1376" name="XLXI_3" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="784" y1="1120" y2="1120" x1="656" />
            <wire x2="992" y1="1120" y2="1120" x1="784" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="832" y1="1184" y2="1184" x1="656" />
            <wire x2="992" y1="1184" y2="1184" x1="832" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="800" y1="1248" y2="1248" x1="656" />
            <wire x2="992" y1="1248" y2="1248" x1="800" />
        </branch>
        <branch name="D">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="336" y="1248" type="branch" />
            <wire x2="336" y1="1248" y2="1248" x1="240" />
            <wire x2="400" y1="1248" y2="1248" x1="336" />
            <wire x2="432" y1="1248" y2="1248" x1="400" />
            <wire x2="400" y1="1248" y2="1456" x1="400" />
            <wire x2="624" y1="1456" y2="1456" x1="400" />
            <wire x2="976" y1="1456" y2="1456" x1="624" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1408" y1="1424" y2="1424" x1="1232" />
            <wire x2="1408" y1="1312" y2="1424" x1="1408" />
            <wire x2="1584" y1="1312" y2="1312" x1="1408" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="1408" y1="1184" y2="1184" x1="1248" />
            <wire x2="1408" y1="1184" y2="1248" x1="1408" />
            <wire x2="1584" y1="1248" y2="1248" x1="1408" />
        </branch>
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1920" y="1280" type="branch" />
            <wire x2="1920" y1="1280" y2="1280" x1="1840" />
            <wire x2="2224" y1="1280" y2="1280" x1="1920" />
        </branch>
        <instance x="432" y="1152" name="XLXI_4" orien="R0" />
        <instance x="432" y="1216" name="XLXI_5" orien="R0" />
        <instance x="432" y="1280" name="XLXI_6" orien="R0" />
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="384" y="1184" type="branch" />
            <wire x2="384" y1="1184" y2="1184" x1="224" />
            <wire x2="432" y1="1184" y2="1184" x1="384" />
        </branch>
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="384" y="1120" type="branch" />
            <wire x2="384" y1="1120" y2="1120" x1="240" />
            <wire x2="432" y1="1120" y2="1120" x1="384" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="320" y="1392" type="branch" />
            <wire x2="320" y1="1392" y2="1392" x1="208" />
            <wire x2="976" y1="1392" y2="1392" x1="320" />
        </branch>
        <iomarker fontsize="28" x="240" y="1120" name="A" orien="R180" />
        <iomarker fontsize="28" x="224" y="1184" name="C" orien="R180" />
        <iomarker fontsize="28" x="240" y="1248" name="D" orien="R180" />
        <iomarker fontsize="28" x="208" y="1392" name="B" orien="R180" />
        <iomarker fontsize="28" x="2224" y="1280" name="Z" orien="R0" />
    </sheet>
</drawing>