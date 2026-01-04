<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="Z" />
        <signal name="XLXN_2" />
        <signal name="C" />
        <signal name="A" />
        <signal name="B" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
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
        <block symbolname="and2b1" name="XLXI_1">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="or2b1" name="XLXI_2">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="576" y="816" name="XLXI_1" orien="R0" />
        <instance x="960" y="912" name="XLXI_2" orien="R0" />
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1296" y="816" type="branch" />
            <wire x2="1296" y1="816" y2="816" x1="1216" />
            <wire x2="1616" y1="816" y2="816" x1="1296" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="896" y1="720" y2="720" x1="832" />
            <wire x2="896" y1="720" y2="784" x1="896" />
            <wire x2="960" y1="784" y2="784" x1="896" />
        </branch>
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="432" y="688" type="branch" />
            <wire x2="432" y1="688" y2="688" x1="288" />
            <wire x2="576" y1="688" y2="688" x1="432" />
        </branch>
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="432" y="752" type="branch" />
            <wire x2="432" y1="752" y2="752" x1="288" />
            <wire x2="576" y1="752" y2="752" x1="432" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="496" y="848" type="branch" />
            <wire x2="496" y1="848" y2="848" x1="288" />
            <wire x2="960" y1="848" y2="848" x1="496" />
        </branch>
        <iomarker fontsize="28" x="288" y="688" name="C" orien="R180" />
        <iomarker fontsize="28" x="288" y="752" name="A" orien="R180" />
        <iomarker fontsize="28" x="288" y="848" name="B" orien="R180" />
        <iomarker fontsize="28" x="1616" y="816" name="Z" orien="R0" />
    </sheet>
</drawing>