<?xml version="1.0" encoding="UTF-8"?>
<html xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <style>table{border-collapse: collapse} td,th{padding: 5px; border: 2px solid black}</style>
    <body>
        <table>
            <tr>
                <th>Roll#</th>
                <th>Name</th>
                <th>Department</th>
            </tr>
            <xsl:for-each select="db/student">
                <tr>
                    <td><xsl:value-of select="name"/></td>
                    <td><xsl:value-of select="dept"/></td>
                    <td><xsl:value-of select="rno"/></td>
                </tr>
            </xsl:for-each>
        </table>
    </body>
</html>