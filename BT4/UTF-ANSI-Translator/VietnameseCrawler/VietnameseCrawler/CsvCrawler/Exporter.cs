using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace VietnameseCrawler.CsvCrawler
{
    public class Exporter : IExporter
    {
        public async Task WriteAsync(IAsyncEnumerable<(string Original, string Stripped)> data, string outputPath)
        {
            // Ensure the directory exists
            string directoryPath = outputPath;
            string filePath = outputPath;

            if (Directory.Exists(outputPath))
            {
                // It's a directory, create a default file name
                filePath = Path.Combine(outputPath, "old-newspaper-vietnamese.txt");
                directoryPath = outputPath;
            }
            else
            {
                // It's probably a file path
                directoryPath = Path.GetDirectoryName(outputPath);
            }

            // Create directory if it doesn't exist
            if (!string.IsNullOrEmpty(directoryPath) && !Directory.Exists(directoryPath))
            {
                Directory.CreateDirectory(directoryPath);
            }

            using (var fs = File.Open(filePath, FileMode.Create, FileAccess.Write, FileShare.None))
            {
                using (var textWriter = new StreamWriter(fs, Encoding.UTF8))
                {
                    await foreach (var (original, stripped) in data)
                    {
                        await textWriter.WriteLineAsync($"{stripped}\t{original}");
                    }
                }
            }
        }
    }
}
