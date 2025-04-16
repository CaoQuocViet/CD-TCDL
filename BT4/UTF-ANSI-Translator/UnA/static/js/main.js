/**
 * UnA - UTF-8/ANSI Converter
 * Frontend JavaScript
 */

document.addEventListener('DOMContentLoaded', () => {
    // Elements
    const dropArea = document.getElementById('dropArea');
    const fileInput = document.getElementById('file-input');
    const fileNameDisplay = document.getElementById('file-name');
    const textInputSwitch = document.getElementById('textInputSwitch');
    const textInputArea = document.getElementById('text-input-area');
    const form = document.getElementById('conversion-form');
    const previewContainer = document.getElementById('preview-container');
    const beforePreview = document.getElementById('before-preview');
    const afterPreview = document.getElementById('after-preview');
    const downloadLink = document.getElementById('download-link');
    
    // File drop functionality
    dropArea.addEventListener('click', () => {
        fileInput.click();
    });
    
    dropArea.addEventListener('dragover', (e) => {
        e.preventDefault();
        dropArea.style.borderColor = '#666';
    });
    
    dropArea.addEventListener('dragleave', () => {
        dropArea.style.borderColor = '#ccc';
    });
    
    dropArea.addEventListener('drop', (e) => {
        e.preventDefault();
        dropArea.style.borderColor = '#ccc';
        
        if (e.dataTransfer.files.length) {
            fileInput.files = e.dataTransfer.files;
            fileNameDisplay.textContent = fileInput.files[0].name;
        }
    });
    
    fileInput.addEventListener('change', () => {
        if (fileInput.files.length) {
            fileNameDisplay.textContent = fileInput.files[0].name;
        } else {
            fileNameDisplay.textContent = 'None';
        }
    });
    
    // Text input switch
    textInputSwitch.addEventListener('change', () => {
        if (textInputSwitch.checked) {
            textInputArea.classList.remove('hidden');
            dropArea.classList.add('hidden');
        } else {
            textInputArea.classList.add('hidden');
            dropArea.classList.remove('hidden');
        }
    });
    
    // Form submission with AJAX
    form.addEventListener('submit', async (e) => {
        e.preventDefault();
        
        const formData = new FormData(form);
        const submitButton = form.querySelector('[type="submit"]');
        
        // Show loading state
        submitButton.disabled = true;
        submitButton.innerHTML = 'Converting...';
        
        try {
            const response = await fetch('/convert', {
                method: 'POST',
                body: formData
            });
            
            if (response.ok) {
                const result = await response.json();
                
                // Show preview
                beforePreview.textContent = result.original.length > 1000 ? 
                    result.original.substring(0, 1000) + '...' : 
                    result.original;
                
                afterPreview.textContent = result.converted.length > 1000 ? 
                    result.converted.substring(0, 1000) + '...' : 
                    result.converted;
                
                // Set download link
                downloadLink.href = result.download_url;
                downloadLink.download = result.filename;
                
                // Show preview container
                previewContainer.classList.remove('hidden');
                
                // Scroll to preview
                previewContainer.scrollIntoView({ behavior: 'smooth' });
            } else {
                // Handle error
                const errorText = await response.text();
                let errorMessage = 'An error occurred during conversion';
                
                try {
                    const errorJson = JSON.parse(errorText);
                    errorMessage = errorJson.error || errorMessage;
                } catch (e) {
                    errorMessage = errorText || errorMessage;
                }
                
                alert('Error: ' + errorMessage);
            }
        } catch (error) {
            console.error('Error:', error);
            alert('Network error or server not responding');
        } finally {
            // Reset button state
            submitButton.disabled = false;
            submitButton.innerHTML = 'Convert';
        }
    });
}); 