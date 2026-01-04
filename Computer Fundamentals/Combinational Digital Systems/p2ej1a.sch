<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_10" />
        <signal name="XLXN_12" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_17" />
        <signal name="XLXN_19" />
        <signal name="A" />
        <signal name="B" />
        <signal name="XLXN_22" />
        <signal name="XLXN_24" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="D" />
        <signal name="XLXN_29" />
        <signal name="C" />
        <signal name="XLXN_31" />
        <signal name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="C" />
        <port polarity="Output" name="Z" />
        <blockdef name="m4_1e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="96" y1="-416" y2="-416" x1="0" />
            <line x2="96" y1="-352" y2="-352" x1="0" />
            <line x2="96" y1="-288" y2="-288" x1="0" />
            <line x2="96" y1="-224" y2="-224" x1="0" />
            <line x2="96" y1="-32" y2="-32" x1="0" />
            <line x2="256" y1="-320" y2="-320" x1="320" />
            <line x2="96" y1="-160" y2="-160" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="176" />
            <line x2="176" y1="-208" y2="-96" x1="176" />
            <line x2="96" y1="-32" y2="-32" x1="224" />
            <line x2="224" y1="-216" y2="-32" x1="224" />
            <line x2="96" y1="-224" y2="-192" x1="256" />
            <line x2="256" y1="-416" y2="-224" x1="256" />
            <line x2="256" y1="-448" y2="-416" x1="96" />
            <line x2="96" y1="-192" y2="-448" x1="96" />
            <line x2="96" y1="-160" y2="-160" x1="128" />
            <line x2="128" y1="-200" y2="-160" x1="128" />
        </blockdef>
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <block symbolname="m4_1e" name="XLXI_1">
            <blockpin signalname="XLXN_24" name="D0" />
            <blockpin signalname="XLXN_25" name="D1" />
            <blockpin signalname="XLXN_26" name="D2" />
            <blockpin signalname="D" name="D3" />
            <blockpin signalname="XLXN_31" name="E" />
            <blockpin signalname="B" name="S0" />
            <blockpin signalname="A" name="S1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_5">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_24" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="and2b2" name="XLXI_7">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_8">
            <blockpin signalname="XLXN_31" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1552" y="1344" name="XLXI_1" orien="R0" />
        <branch name="A">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1360" y="1248" type="branch" />
            <wire x2="1360" y1="1248" y2="1248" x1="1104" />
            <wire x2="1552" y1="1248" y2="1248" x1="1360" />
        </branch>
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1360" y="1184" type="branch" />
            <wire x2="1360" y1="1184" y2="1184" x1="1136" />
            <wire x2="1552" y1="1184" y2="1184" x1="1360" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="960" y1="672" y2="672" x1="832" />
            <wire x2="1248" y1="672" y2="672" x1="960" />
            <wire x2="1248" y1="672" y2="928" x1="1248" />
            <wire x2="1552" y1="928" y2="928" x1="1248" />
        </branch>
        <instance x="576" y="768" name="XLXI_5" orien="R0" />
        <instance x="832" y="992" name="XLXI_6" orien="R0" />
        <branch name="XLXN_25">
            <wire x2="1296" y1="960" y2="960" x1="1056" />
            <wire x2="1296" y1="960" y2="992" x1="1296" />
            <wire x2="1552" y1="992" y2="992" x1="1296" />
        </branch>
        <instance x="512" y="1168" name="XLXI_7" orien="R0" />
        <branch name="XLXN_26">
            <wire x2="1152" y1="1072" y2="1072" x1="768" />
            <wire x2="1152" y1="1056" y2="1072" x1="1152" />
            <wire x2="1552" y1="1056" y2="1056" x1="1152" />
        </branch>
        <branch name="D">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="256" y="1328" type="branch" />
            <wire x2="256" y1="1328" y2="1328" x1="192" />
            <wire x2="304" y1="1328" y2="1328" x1="256" />
            <wire x2="512" y1="1328" y2="1328" x1="304" />
            <wire x2="912" y1="1328" y2="1328" x1="512" />
            <wire x2="576" y1="704" y2="704" x1="304" />
            <wire x2="304" y1="704" y2="1328" x1="304" />
            <wire x2="512" y1="1104" y2="1104" x1="448" />
            <wire x2="448" y1="1104" y2="1184" x1="448" />
            <wire x2="512" y1="1184" y2="1184" x1="448" />
            <wire x2="512" y1="1184" y2="1328" x1="512" />
            <wire x2="928" y1="1120" y2="1120" x1="912" />
            <wire x2="1552" y1="1120" y2="1120" x1="928" />
            <wire x2="912" y1="1120" y2="1328" x1="912" />
        </branch>
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="192" y="960" type="branch" />
            <wire x2="192" y1="960" y2="960" x1="112" />
            <wire x2="352" y1="960" y2="960" x1="192" />
            <wire x2="512" y1="960" y2="960" x1="352" />
            <wire x2="832" y1="960" y2="960" x1="512" />
            <wire x2="576" y1="640" y2="640" x1="352" />
            <wire x2="352" y1="640" y2="960" x1="352" />
            <wire x2="512" y1="944" y2="944" x1="432" />
            <wire x2="512" y1="944" y2="960" x1="512" />
            <wire x2="432" y1="944" y2="1040" x1="432" />
            <wire x2="512" y1="1040" y2="1040" x1="432" />
        </branch>
        <iomarker fontsize="28" x="112" y="960" name="C" orien="R180" />
        <iomarker fontsize="28" x="192" y="1328" name="D" orien="R180" />
        <iomarker fontsize="28" x="1136" y="1184" name="B" orien="R180" />
        <iomarker fontsize="28" x="1104" y="1248" name="A" orien="R180" />
        <instance x="1376" y="1488" name="XLXI_8" orien="R0" />
        <branch name="XLXN_31">
            <wire x2="1440" y1="1488" y2="1568" x1="1440" />
            <wire x2="1552" y1="1568" y2="1568" x1="1440" />
            <wire x2="1552" y1="1312" y2="1568" x1="1552" />
        </branch>
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2128" y="1024" type="branch" />
            <wire x2="2128" y1="1024" y2="1024" x1="1872" />
            <wire x2="2288" y1="1024" y2="1024" x1="2128" />
        </branch>
        <iomarker fontsize="28" x="2288" y="1024" name="Z" orien="R0" />
    </sheet>
</drawing>