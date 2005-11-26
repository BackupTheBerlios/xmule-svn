package.name = "xMule"
package.kind = "exe"
package.language = "c++"
package.target = "xmule"
package.targetextension = ""
project.bindir = "bin"
package.buildoptions = { "`wx-config --cxxflags`" }
package.linkoptions = { "`wx-config --libs`" }

package.files = {
"xApp.cpp",
"xMainFrame/xKadPanel.cpp",
"xMainFrame/xMainFrame.cpp",
"xMainFrame/xSearchPanel.cpp",
"xMainFrame/xServersPanel.cpp",
"xMainFrame/xSharedFilesPanel.cpp",
"xMainFrame/xTransfersPanel.cpp",
"xMainFrame/xOptions/xOptionsDialog.cpp",
"xCore/xSafeFile.cpp",
"xCore/xServer.cpp",
"xCore/xTag.cpp"
}