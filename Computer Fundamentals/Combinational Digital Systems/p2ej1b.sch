<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_24" />
        <signal name="XLXN_25" />
        <signal name="XLXN_33" />
        <signal name="D" />
        <signal name="XLXN_35" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="Z" />
        <signal name="C" />
        <signal name="XLXN_48" />
        <signal name="A" />
        <signal name="B" />
        <signal name="XLXN_53" />
        <signal name="XLXN_54" />
        <signal name="XLXN_55" />
        <signal name="XLXN_56" />
        <signal name="XLXN_57" />
        <port polarity="Input" name="D" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
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
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
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
        <block symbolname="m4_1e" name="XLXI_10">
            <blockpin signalname="XLXN_53" name="D0" />
            <blockpin signalname="D" name="D1" />
            <blockpin signalname="XLXN_35" name="D2" />
            <blockpin signalname="XLXN_53" name="D3" />
            <blockpin signalname="XLXN_48" name="E" />
            <blockpin signalname="C" name="S0" />
            <blockpin signalname="B" name="S1" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="m4_1e" name="XLXI_11">
            <blockpin signalname="XLXN_54" name="D0" />
            <blockpin signalname="XLXN_55" name="D1" />
            <blockpin signalname="D" name="D2" />
            <blockpin signalname="D" name="D3" />
            <blockpin signalname="A" name="E" />
            <blockpin signalname="C" name="S0" />
            <blockpin signalname="B" name="S1" />
            <blockpin signalname="XLXN_24" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_12">
            <blockpin signalname="XLXN_24" name="I0" />
            <blockpin signalname="XLXN_25" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="gnd" name="XLXI_13">
            <blockpin signalname="XLXN_53" name="G" />
        </block>
        <block symbolname="vcc" name="XLXI_14">
            <blockpin signalname="XLXN_35" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_15">
            <blockpin signalname="XLXN_55" name="G" />
        </block>
        <block symbolname="inv" name="XLXI_16">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_54" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_17">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_48" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1584" y="912" name="XLXI_10" orien="R0" />
        <instance x="1584" y="1472" name="XLXI_11" orien="R0" />
        <instance x="2336" y="992" name="XLXI_12" orien="R0" />
        <branch name="XLXN_24">
            <wire x2="2112" y1="1152" y2="1152" x1="1904" />
            <wire x2="2112" y1="928" y2="1152" x1="2112" />
            <wire x2="2336" y1="928" y2="928" x1="2112" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="2112" y1="592" y2="592" x1="1904" />
            <wire x2="2112" y1="592" y2="864" x1="2112" />
            <wire x2="2336" y1="864" y2="864" x1="2112" />
        </branch>
        <instance x="1024" y="480" name="XLXI_13" orien="R0" />
        <instance x="960" y="656" name="XLXI_14" orien="R0" />
        <branch name="XLXN_35">
            <wire x2="1024" y1="656" y2="720" x1="1024" />
            <wire x2="1120" y1="720" y2="720" x1="1024" />
            <wire x2="1120" y1="624" y2="720" x1="1120" />
            <wire x2="1584" y1="624" y2="624" x1="1120" />
        </branch>
        <instance x="992" y="1296" name="XLXI_15" orien="R0" />
        <instance x="1024" y="1392" name="XLXI_16" orien="R0" />
        <iomarker fontsize="28" x="464" y="560" name="D" orien="R180" />
        <branch name="Z">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2672" y="896" type="branch" />
            <wire x2="2672" y1="896" y2="896" x1="2592" />
            <wire x2="2816" y1="896" y2="896" x1="2672" />
        </branch>
        <iomarker fontsize="28" x="2816" y="896" name="Z" orien="R0" />
        <branch name="C">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1440" y="752" type="branch" />
            <wire x2="1440" y1="752" y2="752" x1="1392" />
            <wire x2="1472" y1="752" y2="752" x1="1440" />
            <wire x2="1584" y1="752" y2="752" x1="1472" />
            <wire x2="1472" y1="752" y2="1312" x1="1472" />
            <wire x2="1584" y1="1312" y2="1312" x1="1472" />
        </branch>
        <iomarker fontsize="28" x="1392" y="752" name="C" orien="R180" />
        <instance x="400" y="1280" name="XLXI_17" orien="R0" />
        <branch name="XLXN_48">
            <wire x2="1008" y1="1248" y2="1248" x1="624" />
            <wire x2="1008" y1="880" y2="1248" x1="1008" />
            <wire x2="1584" y1="880" y2="880" x1="1008" />
        </branch>
        <branch name="A">
            <attrtext style="alignment:SOFT-TVCENTER;fontsize:28;fontname:Arial" attrname="Name" x="384" y="1408" type="branch" />
            <wire x2="400" y1="1248" y2="1248" x1="384" />
            <wire x2="384" y1="1248" y2="1376" x1="384" />
            <wire x2="432" y1="1376" y2="1376" x1="384" />
            <wire x2="432" y1="1376" y2="1552" x1="432" />
            <wire x2="1584" y1="1552" y2="1552" x1="432" />
            <wire x2="384" y1="1376" y2="1408" x1="384" />
            <wire x2="384" y1="1408" y2="1440" x1="384" />
            <wire x2="1584" y1="1440" y2="1552" x1="1584" />
        </branch>
        <iomarker fontsize="28" x="384" y="1440" name="A" orien="R90" />
        <branch name="B">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1312" y="816" type="branch" />
            <wire x2="1312" y1="816" y2="816" x1="1248" />
            <wire x2="1408" y1="816" y2="816" x1="1312" />
            <wire x2="1584" y1="816" y2="816" x1="1408" />
            <wire x2="1408" y1="816" y2="1376" x1="1408" />
            <wire x2="1584" y1="1376" y2="1376" x1="1408" />
        </branch>
        <iomarker fontsize="28" x="1248" y="816" name="B" orien="R180" />
        <branch name="XLXN_53">
            <wire x2="1088" y1="336" y2="352" x1="1088" />
            <wire x2="1168" y1="336" y2="336" x1="1088" />
            <wire x2="1360" y1="336" y2="336" x1="1168" />
            <wire x2="1360" y1="336" y2="496" x1="1360" />
            <wire x2="1584" y1="496" y2="496" x1="1360" />
            <wire x2="1168" y1="336" y2="688" x1="1168" />
            <wire x2="1584" y1="688" y2="688" x1="1168" />
        </branch>
        <branch name="D">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="528" y="560" type="branch" />
            <wire x2="528" y1="560" y2="560" x1="464" />
            <wire x2="704" y1="560" y2="560" x1="528" />
            <wire x2="704" y1="560" y2="1360" x1="704" />
            <wire x2="1024" y1="1360" y2="1360" x1="704" />
            <wire x2="816" y1="560" y2="560" x1="704" />
            <wire x2="816" y1="560" y2="864" x1="816" />
            <wire x2="1376" y1="864" y2="864" x1="816" />
            <wire x2="1376" y1="864" y2="1248" x1="1376" />
            <wire x2="1584" y1="1248" y2="1248" x1="1376" />
            <wire x2="880" y1="560" y2="560" x1="816" />
            <wire x2="1584" y1="560" y2="560" x1="880" />
            <wire x2="880" y1="544" y2="560" x1="880" />
            <wire x2="1280" y1="544" y2="544" x1="880" />
            <wire x2="1280" y1="544" y2="1184" x1="1280" />
            <wire x2="1584" y1="1184" y2="1184" x1="1280" />
        </branch>
        <branch name="XLXN_54">
            <wire x2="1296" y1="1360" y2="1360" x1="1248" />
            <wire x2="1312" y1="1072" y2="1072" x1="1296" />
            <wire x2="1296" y1="1072" y2="1360" x1="1296" />
            <wire x2="1584" y1="1056" y2="1056" x1="1312" />
            <wire x2="1312" y1="1056" y2="1072" x1="1312" />
        </branch>
        <branch name="XLXN_55">
            <wire x2="1056" y1="1104" y2="1168" x1="1056" />
            <wire x2="1088" y1="1104" y2="1104" x1="1056" />
            <wire x2="1088" y1="1104" y2="1184" x1="1088" />
            <wire x2="1200" y1="1184" y2="1184" x1="1088" />
            <wire x2="1584" y1="1120" y2="1120" x1="1200" />
            <wire x2="1200" y1="1120" y2="1184" x1="1200" />
        </branch>
    </sheet>
</drawing>