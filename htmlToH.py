Import("env")
import os

html_input = "src/html/index.html"
header_output = "src/indexHtml.h"

print(f"Generating {header_output} from {html_input}...")

# Read HTML file
with open(html_input, 'r', encoding='utf-8') as f:
    html_content = f.read()

# Create header
with open(header_output, 'w', encoding='utf-8') as f:
    f.write('#ifndef ESP32_PLANTSERVER_HTML_H\n#define ESP32_PLANTSERVER_HTML_H\n\n')
    f.write('const char index_html[] PROGMEM = R"rawliteral(\n')
    f.write(html_content)
    f.write('\n)rawliteral";\n')
    f.write('#endif //ESP32_PLANTSERVER_HTML_H')

print(f"Generated {header_output} successfully.")