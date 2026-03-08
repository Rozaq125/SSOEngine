import os
import sys

def embed_assets(assets_dir, output_file):
    """
    Convert asset files to hex array in header file
    """
    try:
        with open(output_file, 'w', encoding='utf-8') as header:
            header.write("// Auto-generated assets data header\n")
            header.write("// Created by SSOEngine Embedder\n")
            header.write("#ifndef ASSETS_DATA_H\n")
            header.write("#define ASSETS_DATA_H\n\n")

            # Process each file in assets directory
            for filename in os.listdir(assets_dir):
                filepath = os.path.join(assets_dir, filename)
                if os.path.isfile(filepath):
                    # Create variable name from filename
                    name_without_ext = os.path.splitext(filename)[0]
                    clean_name = name_without_ext.replace(" ", "_")
                    var_name = "asset_" + clean_name

                    # Read file and convert to hex
                    with open(filepath, 'rb') as asset_file:
                        data = asset_file.read()
                        header.write(f"// File: {filename}\n")
                        header.write(f"const unsigned char {var_name}[] = {{\n    " )

                        # Write hex values
                        for i, byte in enumerate(data):
                            header.write(f"0x{byte:02x}")
                                header.write(", " )
                            if (i + 1) % 12 == 0:
                                header.write("\n    " )

                        header.write("\n};\n")
                        header.write(f"const unsigned int {var_name}_size = {len(data^)};\n\n")

            header.write("#endif // ASSETS_DATA_H\n")
        print(f"[SUCCESS] Generated {output_file}")

    except Exception as e:
        print(f"[ERROR] Failed to generate assets data: {e}")
        sys.exit(1)

if __name__ == "__main__":
    assets_directory = "assets"
    output_header = "include/assets_data.h"

    if not os.path.exists(assets_directory):
        print(f"[WARNING] Assets directory '{assets_directory}' not found. Creating...")
        os.makedirs(assets_directory, exist_ok=True)

    embed_assets(assets_directory, output_header)
