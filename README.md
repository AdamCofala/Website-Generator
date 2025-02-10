# Website-Generator

## Overview
Website-Generator is a basic program designed for school projects that generates a simple website. The program outputs two files:
1. An HTML file for the website's structure.
2. A CSS file for the website's styling.

Users can define various properties of the website, including background images, text formatting, column structures, and footer settings.

## Features
- Generates HTML and CSS files automatically.
- Allows users to set background colors and images.
- Supports text formatting, including font size and color.
- Enables multi-column layouts (1 to 4 columns).
- Provides customization options for footers and column backgrounds.
- Allows image-based backgrounds with adjustable display settings.
- Supports rounded corners for a polished design.

## Input File Specification
The program reads from an input file named `dane.txt`, where each line defines a specific setting. The expected format is as follows:

### General Page Settings
1. Background color of the page.
2. Path to the background image (local file or URL).
3. Image display settings (separated by semicolons):
   - `NIE` – No background image.
   - `RY_TAK` or `RY_NIE` – Repeat vertically.
   - `RX_TAK` or `RX_NIE` – Repeat horizontally.
   - `ROZ_TAK` or `ROZ_NIE` – Stretch image.
   - `FIX_TAK` or `FIX_NIE` – Fixed background.
4. Page title.
5. Title font size.
6. Title font color.
7. Number of content columns (1 to 4).

### Column Settings
8. Content of each column.
9. Font size for each column.
10. Font color for each column.
11. Background color for each column.
12. Option to use an image as a background for each column.
13. If an image is used, its display settings:
    - Repeat vertically/horizontally.
    - Stretch to fit.
    - Fixed background.
14. Border-radius for rounded corners in each column.

### Footer Settings
15. Background color of the footer.
16. Option to use an image as the footer background.
17. If an image is used, its display settings:
    - Repeat vertically/horizontally.
    - Stretch to fit.
    - Fixed background.
18. Footer font color.
19. Footer font size.
20. Footer content.

## Usage
1. Create an input file `dane.txt` with the required settings.
2. Run the program.
3. The program generates `index.html` and `style.css` based on the input file.
4. Open `index.html` in a browser to view the generated website.

## Notes
- Ensure correct formatting in `dane.txt` for accurate rendering.
- Use local paths or valid URLs for images.
- The program supports only basic styling and layout adjustments.
