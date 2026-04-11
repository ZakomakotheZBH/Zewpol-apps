/**
 * Zewpol Cloud - Backend Logic
 */
//this is meant to work in google apps script

// 1. Serve the HTML page
function doGet() {
  return HtmlService.createTemplateFromFile('Index')
    .evaluate()
    .setTitle('Zewpol Cloud')
    .setXFrameOptionsMode(HtmlService.XFrameOptionsMode.ALLOWALL);
}

// 2. Fetch list of files from Google Drive
function getFiles() {
  const files = [];
  const driveFiles = DriveApp.getFiles();
  
  while (driveFiles.hasNext()) {
    const file = driveFiles.next();
    files.push({
      name: file.getName(),
      id: file.getId(),
      url: file.getUrl(),
      size: Math.round(file.getSize() / 1024) + " KB"
    });
  }
  return files;
}

// 3. Handle file uploads
function uploadFile(data, fileName) {
  try {
    const contentType = data.substring(5, data.indexOf(';'));
    const bytes = Utilities.base64Decode(data.split(',')[1]);
    const blob = Utilities.newBlob(bytes, contentType, fileName);
    const file = DriveApp.createFile(blob);
    return "Success: " + file.getName() + " uploaded to Zewpol Cloud!";
  } catch (e) {
    return "Error: " + e.toString();
  }
}
