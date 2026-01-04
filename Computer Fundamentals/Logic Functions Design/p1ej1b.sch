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
        <signal name="Z" />
        <signal name="XLXN_5" />
        <signal name="D" />
        <signal name="A" />
        <signal name="C" />
        <signal name="B" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="B" />
        <blockdef name="nand2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
        </blockdef>
        <blockdef name="nand3b3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="40" y1="-192" y2="-192" x1="0" />
            <circle r="12" cx="52" cy="-192" />
            <line x2="216" y1="-128" y2="-128" x1="256" />
            <circle r="12" cx="204" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
        </blockdef>
        <block symbolname="nand2" name="XLXI_1">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="nand3b3" name="XLXI_2">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="D" name="I2" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_3">
            <blockpin signalname="XLXN_2" name="I0" />
            <blockpin signalname="XLXN_1" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="992" y="1376" name="XLXI_2" orien="R0" />
        <instance x="1440" y="1232" name="XLXI_3" orien="R0" />
        <instance x="976" y="1120" name="XLXI_1" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1328" y1="1024" y2="1024" x1="1232" />
            <wire x2="1328" y1="1024" y2="1104" x1="1328" />
            <wire x2="1440" y1="1104" y2="1104" x1="1328" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1344" y1="1248" y2="1248" x1="1248" />
            <wire x2="1344" y1="1168" y2="1248" x1="1344" />
            <wire x2="1440" y1="1168" y2="1168" x1="1344" />
        </branch>
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1888" y="1136" type="branch" />
            <wire x2="1888" y1="1136" y2="1136" x1="1696" />
            <wire x2="2128" y1="1136" y2="1136" x1="1888" />
        </branch>
        <branch name="D">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="496" y="1184" type="branch" />
            <wire x2="496" y1="1184" y2="1184" x1="432" />
            <wire x2="560" y1="1184" y2="1184" x1="496" />
            <wire x2="576" y1="1184" y2="1184" x1="560" />
            <wire x2="992" y1="1184" y2="1184" x1="576" />
            <wire x2="976" y1="1056" y2="1056" x1="560" />
            <wire x2="560" y1="1056" y2="1184" x1="560" />
        </branch>
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="768" y="1248" type="branch" />
            <wire x2="768" y1="1248" y2="1248" x1="576" />
            <wire x2="992" y1="1248" y2="1248" x1="768" />
        </branch>
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="720" y="1312" type="branch" />
            <wire x2="720" y1="1312" y2="1312" x1="576" />
            <wire x2="992" y1="1312" y2="1312" x1="720" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="720" y="992" type="branch" />
            <wire x2="720" y1="992" y2="992" x1="560" />
            <wire x2="976" y1="992" y2="992" x1="720" />
        </branch>
        <iomarker fontsize="28" x="2128" y="1136" name="Z" orien="R0" />
        <iomarker fontsize="28" x="560" y="992" name="B" orien="R180" />
        <iomarker fontsize="28" x="432" y="1184" name="D" orien="R180" />
        <iomarker fontsize="28" x="576" y="1248" name="A" orien="R180" />
        <iomarker fontsize="28" x="576" y="1312" name="C" orien="R180" />
    </sheet>
</drawing>