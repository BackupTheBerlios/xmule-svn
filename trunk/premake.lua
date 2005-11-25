package.name = "xMule"
package.kind = "exe"
package.language = "c++"
package.target = "xmule"
package.targetextension = ""
project.bindir = "bin"
package.buildoptions = { "`wx-config --cxxflags`" }
package.linkoptions = { "`wx-config --libs`" }

package.files = {
matchfiles("*.h","*.cpp")
}