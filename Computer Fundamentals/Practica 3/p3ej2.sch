<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CLK" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="Q3" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_10" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="INIT" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q3" />
        <port polarity="Input" name="INIT" />
        <blockdef name="cb4cled">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-704" height="640" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-640" y2="-640" x1="384" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-640" y2="-640" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
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
        <blockdef name="and4b4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="40" y1="-192" y2="-192" x1="0" />
            <circle r="12" cx="52" cy="-192" />
            <line x2="40" y1="-256" y2="-256" x1="0" />
            <circle r="12" cx="52" cy="-256" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="64" y1="-112" y2="-112" x1="144" />
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
        <block symbolname="cb4cled" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_30" name="CE" />
            <blockpin signalname="INIT" name="CLR" />
            <blockpin signalname="XLXN_30" name="D0" />
            <blockpin signalname="XLXN_15" name="D1" />
            <blockpin signalname="XLXN_30" name="D2" />
            <blockpin signalname="XLXN_15" name="D3" />
            <blockpin signalname="XLXN_31" name="L" />
            <blockpin signalname="XLXN_30" name="UP" />
            <blockpin name="CEO" />
            <blockpin signalname="Q0" name="Q0" />
            <blockpin signalname="Q1" name="Q1" />
            <blockpin signalname="Q2" name="Q2" />
            <blockpin signalname="Q3" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="vcc" name="XLXI_2">
            <blockpin signalname="XLXN_30" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_4">
            <blockpin signalname="XLXN_15" name="G" />
        </block>
        <block symbolname="and4b4" name="XLXI_10">
            <blockpin signalname="Q3" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="Q1" name="I2" />
            <blockpin signalname="Q0" name="I3" />
            <blockpin signalname="XLXN_33" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_11">
            <blockpin signalname="Q3" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="Q1" name="I2" />
            <blockpin signalname="Q0" name="I3" />
            <blockpin signalname="XLXN_32" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_12">
            <blockpin signalname="XLXN_33" name="I0" />
            <blockpin signalname="XLXN_32" name="I1" />
            <blockpin signalname="XLXN_31" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1344" y="1584" name="XLXI_1" orien="R0" />
        <branch name="CLK">
            <attrtext style="alignment:SOFT-TVCENTER;fontsize:28;fontname:Arial" attrname="Name" x="1040" y="1680" type="branch" />
            <wire x2="1344" y1="1456" y2="1456" x1="1040" />
            <wire x2="1040" y1="1456" y2="1680" x1="1040" />
            <wire x2="1040" y1="1680" y2="1760" x1="1040" />
        </branch>
        <iomarker fontsize="28" x="1040" y="1760" name="CLK" orien="R90" />
        <branch name="Q0">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2112" y="944" type="branch" />
            <wire x2="1616" y1="1632" y2="1712" x1="1616" />
            <wire x2="2032" y1="1632" y2="1632" x1="1616" />
            <wire x2="2032" y1="944" y2="944" x1="1728" />
            <wire x2="2112" y1="944" y2="944" x1="2032" />
            <wire x2="2160" y1="944" y2="944" x1="2112" />
            <wire x2="2032" y1="944" y2="1344" x1="2032" />
            <wire x2="2032" y1="1344" y2="1632" x1="2032" />
            <wire x2="2176" y1="1344" y2="1344" x1="2032" />
        </branch>
        <branch name="Q1">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2128" y="1008" type="branch" />
            <wire x2="1616" y1="1776" y2="1776" x1="1552" />
            <wire x2="1552" y1="1776" y2="1984" x1="1552" />
            <wire x2="1984" y1="1984" y2="1984" x1="1552" />
            <wire x2="1984" y1="1008" y2="1008" x1="1728" />
            <wire x2="2128" y1="1008" y2="1008" x1="1984" />
            <wire x2="2160" y1="1008" y2="1008" x1="2128" />
            <wire x2="1984" y1="1008" y2="1408" x1="1984" />
            <wire x2="1984" y1="1408" y2="1416" x1="1984" />
            <wire x2="1984" y1="1416" y2="1984" x1="1984" />
            <wire x2="2176" y1="1408" y2="1408" x1="1984" />
        </branch>
        <branch name="Q2">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2128" y="1072" type="branch" />
            <wire x2="1616" y1="1840" y2="1840" x1="1536" />
            <wire x2="1536" y1="1840" y2="1968" x1="1536" />
            <wire x2="1920" y1="1968" y2="1968" x1="1536" />
            <wire x2="1920" y1="1072" y2="1072" x1="1728" />
            <wire x2="2128" y1="1072" y2="1072" x1="1920" />
            <wire x2="2160" y1="1072" y2="1072" x1="2128" />
            <wire x2="1920" y1="1072" y2="1472" x1="1920" />
            <wire x2="1920" y1="1472" y2="1968" x1="1920" />
            <wire x2="2176" y1="1472" y2="1472" x1="1920" />
        </branch>
        <branch name="Q3">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="2112" y="1136" type="branch" />
            <wire x2="1600" y1="1648" y2="1904" x1="1600" />
            <wire x2="1616" y1="1904" y2="1904" x1="1600" />
            <wire x2="1856" y1="1648" y2="1648" x1="1600" />
            <wire x2="1856" y1="1136" y2="1136" x1="1728" />
            <wire x2="2112" y1="1136" y2="1136" x1="1856" />
            <wire x2="2160" y1="1136" y2="1136" x1="2112" />
            <wire x2="1856" y1="1136" y2="1536" x1="1856" />
            <wire x2="1856" y1="1536" y2="1648" x1="1856" />
            <wire x2="2176" y1="1536" y2="1536" x1="1856" />
        </branch>
        <iomarker fontsize="28" x="2160" y="944" name="Q0" orien="R0" />
        <iomarker fontsize="28" x="2160" y="1008" name="Q1" orien="R0" />
        <iomarker fontsize="28" x="2160" y="1072" name="Q2" orien="R0" />
        <iomarker fontsize="28" x="2160" y="1136" name="Q3" orien="R0" />
        <instance x="1088" y="1440" name="XLXI_2" orien="R0" />
        <instance x="848" y="1056" name="XLXI_4" orien="R0" />
        <branch name="XLXN_15">
            <wire x2="912" y1="864" y2="928" x1="912" />
            <wire x2="992" y1="864" y2="864" x1="912" />
            <wire x2="992" y1="864" y2="1008" x1="992" />
            <wire x2="1344" y1="1008" y2="1008" x1="992" />
            <wire x2="992" y1="1008" y2="1136" x1="992" />
            <wire x2="1344" y1="1136" y2="1136" x1="992" />
        </branch>
        <iomarker fontsize="28" x="736" y="2048" name="INIT" orien="R180" />
        <branch name="XLXN_30">
            <wire x2="1152" y1="1440" y2="1488" x1="1152" />
            <wire x2="1248" y1="1488" y2="1488" x1="1152" />
            <wire x2="1344" y1="944" y2="944" x1="1248" />
            <wire x2="1248" y1="944" y2="1072" x1="1248" />
            <wire x2="1344" y1="1072" y2="1072" x1="1248" />
            <wire x2="1248" y1="1072" y2="1264" x1="1248" />
            <wire x2="1344" y1="1264" y2="1264" x1="1248" />
            <wire x2="1248" y1="1264" y2="1392" x1="1248" />
            <wire x2="1248" y1="1392" y2="1488" x1="1248" />
            <wire x2="1344" y1="1392" y2="1392" x1="1248" />
        </branch>
        <branch name="INIT">
            <attrtext style="alignment:SOFT-BCENTER;fontsize:28;fontname:Arial" attrname="Name" x="864" y="2048" type="branch" />
            <wire x2="864" y1="2048" y2="2048" x1="736" />
            <wire x2="1008" y1="2048" y2="2048" x1="864" />
            <wire x2="944" y1="1472" y2="1472" x1="848" />
            <wire x2="944" y1="1472" y2="1552" x1="944" />
            <wire x2="1344" y1="1552" y2="1552" x1="944" />
            <wire x2="848" y1="1472" y2="1872" x1="848" />
            <wire x2="1008" y1="1872" y2="1872" x1="848" />
            <wire x2="1008" y1="1872" y2="2048" x1="1008" />
        </branch>
        <instance x="1616" y="1968" name="XLXI_10" orien="R0" />
        <instance x="2176" y="1600" name="XLXI_11" orien="R0" />
        <instance x="2160" y="1936" name="XLXI_12" orien="R0" />
        <branch name="XLXN_31">
            <wire x2="1344" y1="1328" y2="1328" x1="1264" />
            <wire x2="1264" y1="1328" y2="1616" x1="1264" />
            <wire x2="2480" y1="1616" y2="1616" x1="1264" />
            <wire x2="2480" y1="1616" y2="1840" x1="2480" />
            <wire x2="2480" y1="1840" y2="1840" x1="2416" />
        </branch>
        <branch name="XLXN_32">
            <wire x2="2160" y1="1808" y2="1808" x1="2096" />
            <wire x2="2096" y1="1808" y2="1952" x1="2096" />
            <wire x2="2512" y1="1952" y2="1952" x1="2096" />
            <wire x2="2512" y1="1440" y2="1440" x1="2432" />
            <wire x2="2512" y1="1440" y2="1952" x1="2512" />
        </branch>
        <branch name="XLXN_33">
            <wire x2="2016" y1="1808" y2="1808" x1="1872" />
            <wire x2="2016" y1="1808" y2="1872" x1="2016" />
            <wire x2="2160" y1="1872" y2="1872" x1="2016" />
        </branch>
    </sheet>
</drawing>